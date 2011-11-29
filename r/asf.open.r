# Opens connection using provided <fileName>.
# Both plain and gzipped files are supported.
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
