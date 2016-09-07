# GNU makefile


get = x3dom.js x3dom.css

build: $(get)

$(get):
	wget http://examples.x3dom.org/example/$@ -O $@

clean:
	rm -f $(get)
