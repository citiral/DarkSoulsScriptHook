
function inventory:getItem(index)
	return ds2:readInt(inventory:getItemBasePointer(index), 0x14)
end

function inventory:setItem(index, data)
	ds2:writeInt(inventory:getItemBasePointer(index), 0x14, data)
end
