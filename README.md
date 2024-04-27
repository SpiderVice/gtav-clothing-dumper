# GTAV Clothing Dumper
## An ASI script to generate a GXT label lookup for every drawable texture for every MP Ped Component in GTA V.
### Brief
This script generates a JSON file containing GXT labels for all drawables of every ped component of an online character.

For lack of better ideas, **the button to trigger the dump is F** (or whatever the "Enter Vehicle" control is). **This creates a `clothingdump.json` file in your game's directory**.

The schema is as follows:

```typescript
/* This is the JSON root */
interface IClothingDump {
	"mp_f_freemode_01": PedClothing;
	"mp_m_freemode_01": PedClothing;
}

type PedClothing = Record<PedComponent, ComponentDrawables>;
type ComponentDrawables = Record<number, DrawableTextures>;
type DrawableTextures = Record<number, GxtLabel>;
type GxtLabel = string;

type PedComponent = |
	"head" |
	"beard" |
	"hair" |
	"upper" |
	"lower" |
	"hands" |
	"feet" |
	"teeth" |
	"accessories" |
	"armour" |
	"badge" |
	"torso";
```

### Installation & usage
The latest dump should be available in the `dist/` directory of this repo.

#### Dumping
1. Download [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/) and place `dinput8.dll` and `ScriptHookV.dll` in your GTAV directory.
2. Download [the latest compiled dumper script from the Releases page](https://github.com/tomezpl/gtav-clothing-dumper/releases/latest) and place GTAVClothingDumper.asi in your GTAV directory.
3. Launch GTAV
4. Load into story mode
5. Once spawned in, press F.
6. Your character will change to the online character. There should now be a `clothingdump.json` file in your GTAV directory.

### Building
1. Download [the ScriptHookV SDK](http://www.dev-c.com/gtav/scripthookv/).
2. Extract the SDK to a folder and set an environment variable named `SCRIPTHOOKV_SDK` pointing to the extracted folder.
3. Clone this repo.
4. Open the solution in Visual Studio 2022
5. Build
6. Copy the ASI from `bin/Release` and place it in your GTAV directory.

### Thanks
Big thanks to [Alexander Blade](http://www.dev-c.com/) for [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/) and [root-cause (GitHub)](https://github.com/root-cause) for the [PedComponent struct layout](https://gist.github.com/root-cause/3b80234367b0c856d60bf5cb4b826f86).