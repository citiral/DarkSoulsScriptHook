dofile("scripts\\darksouls2\\lua.lua")

--print("hello")

--count = 0

--for i = 0,49 do
	--print("Item " .. i .. " is " .. IdToString(inventory:getItem(i)) .. " (hex: " .. string.format("%x", inventory:getItem(i)) .. ")")
	---if IdToString(inventory:getItem(i)) ~= "nil" then
	---	count = count  + 1
	---end
--end

--print(" item count is " .. count)

selected = inventory:selectedItem()
print("selected item is " .. string.format("0x%X", selected))
index = inventory:findItem(selected)
print("index is " .. index)
--inventory:setQuantity(index, 40)
--print("count is " .. inventory:getQuantity(index))
--print("replacing item ")
--inventory:setItem(index, 0x039C9B38)

print("hp is " .. player:getHealth())
--print("vigor is " .. player:getVigor())
--for i = 0, 120 do
	ds2:pressKey(Keys.LEFT)
--end
--for i = 0, 2000 do
--	ds2:pressKey(Keys.A)
--	ds2:pressKey(Keys.UP)
--end
--player:setHealth(player:getHealth() - 100)
