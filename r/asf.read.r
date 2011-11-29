indexof = function(where, what)
{
	regexpr(what, where)[1]
}

asf.open = function(fileName)
{
	if (indexof(fileName, ".asf.gz") > 0)
	{
		gzfile(fileName, "rt")
	}
	else if (indexof(fileName, ".asf") > 0)
	{
		file(fileName, "rt")
	}
	else
	{
		throw("Unknown file format (unknown extension).")
	}
}

asf.read.head = function(connection)
{
	head = NULL
	
	isBodyFound = 0
	while (!isBodyFound && length((line = readLines(connection, 1))))
	{
		index = indexof(line, " ")
		
		key = substring(line, 1, index - 1)
		value = substring(line, index + 1)
		
		if (key != "ASCII_DATA")
		{
			head[key] = value
		}
		else
		{
			isBodyFound = 1
		}		
	}
	
	if (!isBodyFound)
	{
		throw ("Head is not followed by body.")
	}
	
	head
}

asf.read.frame = function(connection, frameHeight)
{
	frame = list()
	
	if (!length((line = readLines(connection, 1))) || line != "")
	{
		throw("Can't find blank line before frame head.")
	}
	
	if (!length((line = readLines(connection, 1))))
	{
		throw("Can't find frame head.")
	}
	
	index = indexof(line, "p")
	if (index > 0)
	{
		frame["timestamp"] = as.numeric(substring(line, index + 1))
	}
	
	if (!isTRUE(frame["timestamp"]))
	{
		frame["timestamp"] = -1
	}

	frame["data"][[1]] = read.table(connection, sep=",", nrows=frameHeight)
	
	frame
}

asf.read = function(fileName)
{
	connection = asf.open(fileName)
	
	head = asf.read.head(connection)
	
	framesCount = as.numeric(head["END_FRAME"]) - as.numeric(head["START_FRAME"]) + 1
	frameHeight = as.numeric(head["ROWS"])
	
	body = list()
	
	for (i in 1:framesCount)
	{
		body[[i]] = asf.read.frame(connection, frameHeight)
	}
	
	asf = list()

	asf[["head"]] = head
	asf[["body"]] = body
	
	asf
}