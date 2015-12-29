running = false

function start()
end
function stop()
end
function update(dt)
end

function getPointer()
	pptr = ptr.readptr(ptr.add(ptr.base(), 0x00F7A644))
	if ptr.toint(pptr) ~= 0 then
		pptr = ptr.readptr(ptr.add(pptr, 0x3C))
		if ptr.toint(pptr) ~= 0 then
			return pptr
		else
			return ptr.make(0)
		end
	else
		return ptr.make(0)
	end
end

function InternalUpdate(dt)
	--if we are running and player is 0, stop running
	if running == true then
		pptr = getPointer()

		if ptr.toint(pptr) == 0 then
			running = false
			stop()
		else
			update(dt)
		end

	else 
		pptr = getPointer()

		if ptr.toint(pptr) ~= 0 then
			running = true
			loadHooks()
			start()
		end
	end
end

function loadHooks()
	--Create generic helper functions
	function generateWritei32(p)
		return function(data)
			ptr.writei32(p, data)
		end
	end

	function generateReadi32(p)
		return function()
			return ptr.readi32(p)
		end
	end

	function generateReadf32(p)
		return function()
			return ptr.readf32(p)
		end
	end

	--function ds:writeBytes(offset, ...)
	--	local arg={...}
	--	for i,v in ipairs(arg) do
	--		print("writing " .. i )
	--    	ds:writeByte(ds2:baseAddress(), offset + i - 1, v)
	--    end
	--end

	dofile("scripts/darksouls/player.lua")
end
