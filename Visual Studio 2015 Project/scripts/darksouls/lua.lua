
--Create generic helper functions
function generateWriteInt(base, offset)
	return function(data)
		ds:writeInt(base, 0x1, data)
	end
end

function generateReadInt(base, offset)
	return function()
		return ds:readInt(base, offset, data)
	end
end

function generateWriteShort(base, offset)
	return function(data)
		ds:writeShort(base, offset, data)
	end
end

function generateReadShort(base, offset)
	return function()
		return ds:readShort(base, offset, data)
	end
end

function ds:writeBytes(offset, ...)
	local arg={...}
	for i,v in ipairs(arg) do
		print("writing " .. i )
    	ds:writeByte(ds2:baseAddress(), offset + i - 1, v)
    end
end

--include neccessary files
dofile("scripts\\darksouls\\player.lua")
--dofile("scripts\\darksouls\\inventory.lua")
dofile("scripts\\darksouls\\items.lua")
dofile("scripts\\darksouls\\input.lua")