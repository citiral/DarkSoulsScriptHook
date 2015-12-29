require 'scripts//darksouls'

timer = 0

function start()
	prevHealth = player.getHealth()
	curHealth = player.getHealth()
	lastdiff = 0
end

function stop()

end

function update(dt)
	curHealth = player.getHealth()

	diff = prevHealth - curHealth

	if diff > 0 then
		newsouls = player.getSouls() - diff
		if newsouls < 0 then
			newsouls = 0
		end
		player.setSouls(newsouls)
		timer = 2
		lastdiff = diff
	end

	prevHealth = curHealth

	if timer > 0 then
		drawing.drawText("took " .. lastdiff .. " soul damage!", 20, 20)
		timer = timer - dt
	end

end