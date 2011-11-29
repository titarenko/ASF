# Returns index of first occurrence of <what> in <where>,
# or -1 if <what> can't be found in <where>.
indexof = function(where, what)
{
	regexpr(what, where)[1]
}
