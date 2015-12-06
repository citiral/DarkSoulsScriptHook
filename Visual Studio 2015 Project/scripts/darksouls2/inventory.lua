--linked list: prev = 0x0, next = 0x8


function inventory:selectedItem(data)
	ptr = ds2:readPtr(ds2:baseAddress(), 0x160ABC0)
	ptr = ds2:readPtr(ptr, 0x4F0)
	return  ds2:readInt(ptr, 0x394)
end

function inventory:getItem(index)
	return ds2:readInt(inventory:getItemBasePointer(index), 0x14)
end

function inventory:setItem(index, data)
	ds2:writeInt(inventory:getItemBasePointer(index), 0x14, data)
	ds2:writeInt(inventory:getItemBasePointer(index), 0x18, data)
end

function inventory:setQuantity(index, quantity)
	ds2:writeInt(inventory:getItemBasePointer(index), 0x20, quantity)
end

function inventory:getQuantity(index)
	return ds2:readInt(inventory:getItemBasePointer(index), 0x20)
end

function inventory:findItem(data)
	missed = 0
	item = -1
	index = 0
	while missed < 2 do
		item = inventory:getItem(index)
		print("iter item " .. item)
		if item == data then
			return index
		end
		index = index + 1
	end
end
