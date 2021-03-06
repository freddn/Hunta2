
function AddItem(filename, id,count,x,y)
	print("Add item")
	file = io.open(filename,"a")
	if file ~= nil then
		io.output(file)
		io.write("loadItem(",id,", ",count,", ",x,", ",y,")\n")
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function DeleteItem(filename, id, count, x, y)
	file = io.open(filename,"r")
	if file ~= nil then
		content = {}

		for line in file:lines() do
			j = 1
			item = {}
			for str in string.gmatch(line,'%S+') do
				item[j] = str
				j = j + 1
			end
			if tonumber(item[1]) == id and tonumber(item[2]) >= count and 
					tonumber(item[3]) == x and tonumber(item[4]) == y then
				i = tonumber(item[2]) - count
				print("Removed item\n")
				if i == 0 then
					-- do nothning
				else
					content[#content+1] = "loadItem(" .. item[1] .. ", " .. i .. ", " .. item[3] .. ", " .. item[4] .. ")"
				end
			else
				content[#content+1] = line -- add line to vector
			end
		end
		io.close(file)
		file = io.open(filename,"w+")
		io.output(file)
		
		for i = 1, #content do
			io.write(string.format("%s\n",content[i]))
		end
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function ClearInventory(filename)
	file = io.open(filename,"w+")
	if file ~= nil then
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function NewInventoryFile(filename)
	file = io.open(filename, "w")
	if file == nil then
		io.output(file)
		io.write("-- ItemID count x y\n")
		io.close(file)
	else
		print("File already exists.")
	end
end



