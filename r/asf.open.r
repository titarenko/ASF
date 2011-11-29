# Opens connection using provided <fileName>.
# Both plain and gzipped files are supported.
# Interaction mode defines how file will be used:
# for reading ("rt") or for writing ("wt").
asf.open = function(fileName, interactionMode)
{
	if (indexof(fileName, ".asf.gz") > 0)
	{
		gzfile(fileName, interactionMode)
	}
	else if (indexof(fileName, ".asf") > 0)
	{
		file(fileName, interactionMode)
	}
	else
	{
		throw("Unknown file format (unknown extension).")
	}
}

# Alias for <asf.open> with "rt" as <interactionMode>.
asf.open.read = function(fileName)
{
	asf.open(fileName, "rt")
}

# Alias for <asf.open> with "wt" as <interactionMode>.
asf.open.write = function(fileName)
{
	asf.open(fileName, "wt")
}
