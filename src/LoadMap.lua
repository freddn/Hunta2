
function getTiles(id)
	filename = "data/maps/" .. tostring(id) .. "/tiles"
	print(filename)
	map = io.open(filename,"r")
	if map == nil then
		print("Map not found.")
		return
	end
	io.input(map)
    word = io.read()
	ini = {}
	i = 1
    for str in string.gmatch(word,'%w+') do
		ini[i] = str
		i = i + 1
	end

	setDimensions(ini[2],ini[4])

	num_tiles = tonumber(ini[2]) * tonumber(ini[4])
	i = 1
	done = false
	while (done ~= true) do

		word = io.read()
		if word == nil then 
			done = true
			return
		end
		j = 1
		tile = {}
		for str in string.gmatch(word,'%S+') do
			tile[j] = str
			j = j + 1
		end
		a = table.getn(tile)
		if a ~= 12 then
			print("Bad tile format.")
			return
		elseif a == 12 then
			loadTile(filename,tile[2],tile[4],tile[6],tile[8],tile[10],tile[12])
		end
		i = i + 1
	end
	io.close(map)
end


