--linked list: prev = 0x0, next = 0x8

--get the id of the item currently selected in the inventory
function inventory:selectedItem(data)
	local ptr = ds2:readPtr(ds2:baseAddress(), 0x160ABC0)
	ptr = ds2:readPtr(ptr, 0x4F0)
	return  ds2:readInt(ptr, 0x394)
end

function inventory:getOffset(index)
	return index * 0x28
end

function inventory:firstItem(ptr)
	return ds2:addPtr(inventory:getItemBasePointer(), inventory:getOffset(2))
end

function inventory:firstHead(ptr)
	return ds2:addPtr(inventory:getHeadBasePointer(), inventory:getOffset(0))
end

function inventory:firstWeapon(ptr)
	return inventory:getWeaponBasePointer()
end

--gets the next item from the index slot of the inventory
function inventory:nextItem(ptr)
	return ds2:readPtr(ptr, 0x08)
end

--gets the previous item from the index slot of the inventory
function inventory:prevItem(ptr)
	return ds2:readPtr(ptr, 0x00)
end

--sets the item id at the ptr slot of the inventory
function inventory:setId(ptr, data)
	ds2:writeInt(ptr, 0x14, data)
	ds2:writeInt(ptr, 0x18, data)
end

--gets the item Id of the index slot of the inventory
function inventory:getId(ptr)
	return ds2:readInt(ptr, 0x14)
end

--sets the quantity for the index slot of the inventory
function inventory:setQuantity(ptr, quantity)
	ds2:writeInt(ptr, 0x20, quantity)
end

--gets the quantity for the index slot of the inventory
function inventory:getQuantity(ptr)
	return ds2:readInt(ptr, 0x20)
end

--find the ptr of the first item in the inventory with as ID == data
--this function runs in O(n), so it is best to cache this value
function inventory:findItem(data)
	local item = inventory:firstItem()
	
	while not ds2:isNull(item) do
		local id = inventory:getId(item)
		if id == data then
			return item
		end
		item = inventory:nextItem(item)
	end

	return ds2:makePtr(0)
end
