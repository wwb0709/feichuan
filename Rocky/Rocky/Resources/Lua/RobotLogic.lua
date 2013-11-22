local function CallFucnCallback1(sender)
    sender:idle()
    sender:hit()
end

function findTarget(robot,targetPos)
    
    local robotX,robotY=robot:getPosition()
    
    if robotX > targetPos.x and robotX-targetPos.x>300 then
        return
    end

    --检测是否击中
    if math.abs(robotY - targetPos.y) < 10 and math.abs(robotX - targetPos.x) < 30 then
        robot:hit();
        return
    end
    
    local robotState=robot:getState()
    --如果机器人处于idle状态,则使机器人寻找目标，并攻击
    if robotState==kRoleStateIdle then

        local toXPos,toYPos;
        local xDistance = math.abs(robotX - targetPos.x) 
        local yDistance = math.abs(robotY - targetPos.y)
        
        if xDistance > 60 and yDistance > 40 then
            
            local toXOffset=math.random(20,30)
            local toYOffset=math.random(0,10)
            
            if robotX > targetPos.x then
                toXPos=targetPos.x+toXOffset
            else 
                toXPos=targetPos.x-toXOffset
            end
            
            if robotY > targetPos.y then
                toYPos=targetPos.y+toYOffset
            else 
                toYPos=targetPos.y-toYOffset
            end
            
        else 
            
            if targetPos.x > robotX then
                toXPos=math.random(robotX,targetPos.x+targetPos.x-robotX)
            else
                toXPos=math.random(targetPos.x,robotX+robotX-targetPos.x)
            end
            
            toYPos=math.random(40,120)
        end

        
        --播放move动画
        robot:move()

        --设置机器人的脸的朝向
        if toXPos > robotX  then
            robot:setDirection(kRoleDirectionRight)
        else
            robot:setDirection(kRoleDirectionLeft)
        end
        
        local moveTime=math.random(1.0,3.0)
        --移动机器人到指定坐标
        local moveTo=CCMoveTo:create(moveTime, ccp(toXPos,toYPos))
        local callBackIdle=CCCallFuncN:create(CallFucnCallback1)
        
        local actionArray=CCArray:create()
        actionArray:addObject(moveTo)
        actionArray:addObject(callBackIdle)
        
        local sequeneAction=CCSequence:create(actionArray)
        robot:runAction(sequeneAction)
    end

    

end

