
function loadInventory(filename)
	inv = io.open(filename,"r")
	if inv == nil then
		print("Inventory not found.")
		return
	end
	io.input(inv)
	word = io.read()
	i = 1
	done = false
	while (done ~= true) do

		word = io.read()
		if word == nil then 
			done = true
			return
		end
		
		j = 1
		item = {}
		for str in string.gmatch(word,'%S+') do
			item[j] = str
			j = j + 1
		end
		
		a = table.getn(item)
		if a ~= 4 then
			print("Bad item format.")
			return
		elseif a == 4 then
			loadItem(filename,item[1],item[2],item[3],item[4])
		end
		i = i + 1
	end
	io.close(inv)
end

