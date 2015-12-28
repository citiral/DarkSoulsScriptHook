dofile("scripts\\darksouls\\lua.lua")

--print("hello")

--count = 0

--for i = 0,49 do
	--print("Item " .. i .. " is " .. IdToString(inventory:getItem(i)) .. " (hex: " .. string.format("%x", inventory:getItem(i)) .. ")")
	---if IdToString(inventory:getItem(i)) ~= "nil" then
	---	count = count  + 1
	---end
--end

--print(" item count is " .. count)

--selected = inventory:selectedItem()
--item = inventory:firstHead()
--index = 0
--print("base is " .. string.format("%x", ds2:fromPtr(item)))
--while not ds2:isNull(item) do
--	print("item " .. index .. " is " .. IdToString(inventory:getId(item)))
--	item = inventory:nextItem(item)
--	index = index + 1 
--end

--inventory:setQuantity(inventory:findItem(60151000), 20)
--ds:writeInt(player:getBasePointer(), 0x2d4, ds:readInt(player:getBasePointer(), 0x2d4)+10)

ds:writeInt(player:getBasePointer2(), 0x8c, 150)
--player:setHealth(200)
player:setSouls(1600)

--print("bytes are " .. string.format("%x", ds2:readByte(ds2:baseAddress(),  0x16721A+1)))
--ds2:writeShort(ds2:baseAddress(), 0x16721A, 0x8389)
--ds2:writeInt(ds2:baseAddress(), 0x16721A+2, 0x00000168)
--ds2:writeBytes( 0x16721A, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90)
--ds2:writeBytes( 0x16721A, 0x89, 0x83, 0x68, 0x01, 0x00, 0x00)

--ds2:writeShort(ds2:baseAddress(), 0x16721A, 0x9090)
--ds2:writeInt(ds2:baseAddress(), 0x16721A+2, 0x90909090)

--inventory:setId(inventory:findItem( 0x039B4F30 ), 0x030A32C0)

--index = inventory:findItem(selected)
--print("index is " .. index)
--inventory:setQuantity(index, 40)
--print("count is " .. inventory:getQuantity(index))
--print("replacing item ")
--inventory:setItem(index, 0x039C9B38)

--print("hp is " .. player:getHealth())
--print("vigor is " .. player:getVigor())
--for i = 0, 120 do
--	ds2:pressKey(Keys.LEFT)
--end
--for i = 0, 2000 do
--	ds:pressKey(Keys.A)
--	ds:pressKey(Keys.UP)
--end
--player:setHealth(player:getHealth() - 100)
