require 'scripts//darksouls'

--THIS FUCKING CALLS A DARK SOULS INTERNAL FUNCTION
--funcaddr = ptr.add(ptr.base(), 0xA67560)
--func.call_void_i32_ptr(funcaddr, player.ptr1, 2000)

healths = {}

function update(dt)
	--player.callSetSouls(80000)
	--player.callSetHealth(00)--drawing.drawText("func addr = " .. lib.ptrToString(funcaddr), 500, 30)
	drawing.drawText("player pointer 2 is " .. lib.ptrToString(player.ptr2), 100, 100)
	--func.call_void_eax_edx_1arg_pop_1(ptr.add(ptr.base(), 0xbcd760), 500, 0x9, player.ptr2)
	func.call_void_ecx_edx_edi(ptr.add(ptr.base(), 0xBCD760), player.ptr2, 0x0019fa18, 0x3)

--	timer = timer + dt*10
--
--	if timer > 1 then
--		timer = timer - 1
--		player.setHealth(player.getHealth() - 1)
--		player.setSouls(player.getSouls() + 1)
--	end



	--drawing.drawText("souls: " + player.getSouls(), 50, 50);

--	x = x + 0.2
--	drawing.drawText("decrease hp script active! cur hp = " .. player.getHealth(), 300, x)
	--ptr.writei32(ptr.add(player.ptr, 0x2D4), 50)
	--drawing.drawText("health is: " .. ptr.readi32(ptr.add(player.ptr, 0x2D4)), 300, x)
	--player.setHealth(200);
	--drawing.drawText("health is: " .. player.getHealth(), 300, x)

	--esi = ptr.toint(ptr.readptr(ptr.add(ptr.base(), 0xF7A644)));
	--drawing.drawText("esi is " .. lib.ptrToString(ptr.readptr(ptr.add(ptr.base(), 0xF7A644))), 500, 50);
	--thefunc = ptr.add(ptr.base(), 0xa3d090);
	--drawing.drawText(lib.ptrToString(thefunc) .. " is ptr", 400, 100);

	--stop = false
	--index = 0
	--wrapindex = 0
	--enemies = ""



	--while stop ~= true do	
	--	enemy = func.call_ptr_eax_ecx_edx_esi(thefunc, 0x10024000 + index, 15, 0x10024000 + index, esi);
--
--		if ptr.toint(enemy) == 0 then
--			stop = true
--			break
--		end

--		hp = ptr.readi32(ptr.add(enemy, 0x2d4))
--
--		healths[enemy] = hp

--		enemies = enemies ..  "E " .. index .. " = " .. lib.ptrToString(enemy) .. " hp = " .. hp .. " "
		
--		index = index + 1
--		wrapindex = wrapindex + 1
--
--		if wrapindex > 4 then
--			wrapindex = 0
--			enemies = enemies .. "\n"
--		end

--	end
--	enemies = "there are " .. index .. " enemies\n" .. enemies
--	drawing.drawText(enemies, 1, 10);



	
--	lib.flushDebugFile();

	
	--drawing.drawText("ptr: 0x" ..   lib.ptrToString(ptr.readptr(ptr.add(ptr.base(), 0x00F7A644))), 200, 200);
	
end