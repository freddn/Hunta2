x = 0

playerXPos = 0
playerYPos = 0



function Main()
    --while true do
        checkEvents()
        --yield()
    --end

end

function checkEvents()
    playerXPos = getPlayerX()
    playerYPos = getPlayerY()
    x = x + 1
    if x > 400 then
        if playerXPos > 400 then
            print ("data/maps/1/map.lua - checkEvents() -> ( x > 400, x=" .. playerXPos .. " )")
        end

        if playerYPos > 400 then
            print ("data/maps/1/map.lua - checkEvents() -> ( y > 400, y=" .. playerYPos .. " )")
        end
        --print "checking for events in lua..."
        x = 0
    end

end
