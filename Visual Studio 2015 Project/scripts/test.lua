dofile("scripts\\darksouls2\\lua.lua")

print("hello")

count = 0

for i = 0,46 do
	print("Item " .. i .. " is " .. IdToString(inventory:getItem(i)) .. " (hex: " .. string.format("%x", inventory:getItem(i)) .. ")")
	if IdToString(inventory:getItem(i)) ~= "nil" then
		count = count  + 1
	end
end

print(" item count is " .. count)

print("hp is " .. player:getHealth())
print("vigor is " .. player:getVigor())
--player:setHealth(player:getHealth() - 100)
