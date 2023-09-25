HUGO_BIN=hugo

.PHONY: build demo stripped

stripped: build
	$(shell find public/ | grep \.html$ | xargs sed -i '/^ *$$/d' )

build:
	$(HUGO_BIN) 

demo:
	$(HUGO_BIN) server -D
