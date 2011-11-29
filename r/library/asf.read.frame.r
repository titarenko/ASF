# Reads ASF frame as named list with keys "timestamp" and "data",
# where data is actually frame itself.
asf.read.frame = function(connection, frameHeight)
{
	frame = list()
	
	if (!length((line = readLines(connection, 1))) || line != "")
	{
		stop("Can't find blank line before frame head.")
	}
	
	if (!length((line = readLines(connection, 1))))
	{
		stop("Can't find frame head.")
	}
	
	index = indexof(line, "p")
	if (index > 0)
	{
		frame[["timestamp"]] = as.numeric(substring(line, index + 1))
	}
	
	if (!isTRUE(frame[["timestamp"]]))
	{
		frame[["timestamp"]] = -1
	}

	frame[["data"]] = read.table(connection, sep=",", nrows=frameHeight)
	
	frame
}
