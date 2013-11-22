
-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

local function doTest()
end

function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)


    local bgMusicPath = CCFileUtils:sharedFileUtils():fullPathFromRelativePath("song0.mp3")
    SimpleAudioEngine:sharedEngine():playBackgroundMusic(bgMusicPath, true)
    local effectPath = CCFileUtils:sharedFileUtils():fullPathFromRelativePath("effect1.wav")
    SimpleAudioEngine:sharedEngine():preloadEffect(effectPath)

end

xpcall(main, __G__TRACKBACK__)
