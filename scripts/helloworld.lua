require 'scripts//darksouls'

time = 0

function stop()

end

function start()

end

function update(dt)
	time = time + dt
	drawing.drawText("hello world!", math.sin(time) * 300 + 650, 100)
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

	--drawing.drawText("ptr: 0x" .. lib.ptrToString(ptr.readptr(ptr.add(ptr.base(), 0x00F7A644))), 200, 200);
	--drawing.drawText("ptr: 0x" ..   lib.ptrToString(ptr.readptr(ptr.add(ptr.base(), 0x00F7A644))), 200, 200);
	
end