
function AddItem(filename, id,count,x,y)
	file = io.open(filename,"a")
	if file != nil then
		io.output(file)
		io.write(id,count,x,y,"\n")
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function DeleteItem(filename, id, count, x, y)
	file = io.open(filename,"r")
	if file != nil then
		content = {}

		for line in file:lines() do
			j = 1
			item = {}
			for str in string.gmatch(line,'%S+') do
				item[j] = str
				j = j + 1
			end
			if item[1] == id and item[2] == count and item[3] == x and item[4] == y then
				--do nothing
				print("Removed item\n")
			else
				content[#content+1] = line -- add line to vector
			end
		end
		io.close(file)
		file = io.open(filename,"w+")
		
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
	if file != nil then
		io.close(file)
	else
		print("File not found:", filename)
	end
end

function NewInventoryFile(filename)
	file = io.open(filename, "w")
	if file == nil then
		io.output(file)
		io.write("ItemID count x y\n")
		io.close(file)
	else
		print("File already exists.")
	end
end



