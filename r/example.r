# reading of entire ASF file
asf = asf.read("../examples/example1.asf")

# in order to access value from header 
# you should do something like this
# (number of rows, or frame height)
# please take note that these values are strings
asf[["head"]]["ROWS"]

# also you can iterate through all values
# that are stored in header
for (index in 1:length(asf[["head"]]))
{
	print(sprintf("%s = %s", 
		names(asf[["head"]])[index], 
		asf[["head"]][index]))
}

# if you want to obtain i-th frame
# you should try expression like this
# (accessing 5th frame)
fifth = asf[["body"]][[5]]

# in order to obtain timestamp for
# selected frame, try this construction
# (value of -1 is nothing but "N/A")
fifth[["timestamp"]]

# in order to get element value of
# given frame, you should access next way
# (element at x=3, y=9)
fifth[["data"]][3, 9]
