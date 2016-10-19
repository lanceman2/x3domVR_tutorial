// Utility function that tries to find the name of
// a function and than runs said function.
// TODO: How can we add arguments?
// Credit:
// https://www.sitepoint.com/html5-full-screen-api/

var pfx = ["webkit", "moz", "ms", "o", ""];

function RunPrefix(obj, method) {
    var p = 0, m, t;
    while(p < pfx.length && !obj[m]) {
        m = method;
        if(pfx[p] == "")
            m = m.substr(0,1).toLowerCase() + m.substr(1);
	    m = pfx[p] + m;
        t = typeof obj[m];
        if(t != "undefined") {
            // save the prefix we found
	    pfx = [pfx[p]];
	    return (t == "function" ? obj[m]() : obj[m]);
        }
        p++;
    }
}

