# Reads ASF header (key/value storage) as named vector.
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
