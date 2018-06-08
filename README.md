# ofxOscRawPacket

create raw packet from ofxOscMessage

## API

* `ofBuffer ofxOscToBuffer(const ofxOscMessage &mess)`
* `ofBuffer ofxOscToBuffer(const ofxOscBundle &bundle)`

create raw osc packet

* `std::vector<ofxOscMessage> ofxOscFromBuffer(const ofBuffer &buf)`

create ofxOscMessages from raw osc packet

## Example

please use `ProjectGenerator` to create Project file after this command:

```bash
cd path/to/this_repo
git submodule update --init --recursive
```

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!

If you get happy with using this addon, and you're rich, please donation for support continuous development.

Bitcoin: `17AbtW73aydfYH3epP8T3UDmmDCcXSGcaf`