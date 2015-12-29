require 'scripts//darksouls'

function start()

end

function stop()

end

function update(dt)
	nowhealth = player.getHealth()
	
	player.setMaxStamina(nowhealth * 0.21)

end
