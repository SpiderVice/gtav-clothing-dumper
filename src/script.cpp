#include "script.h"
#include "component-data.h"
#include <iostream>
#include <fstream>

// Keys to use for each component - the string index needs to match the component ID (e.g. element 3 needs to be "upper")
const char* pedComponents[] =
{
	"head",
	"beard",
	"hair",
	"upper",
	"lower",
	"hands",
	"feet",
	"teeth",
	"accessories",
	"armour",
	"badge",
	"torso"
};

// MP ped names
const char* mpPeds[] =
{
	"mp_f_freemode_01",
	"mp_m_freemode_01"
};

void main()
{
	while (true)
	{
		// Listen for the Vehicle Enter key being pressed (usually F on PC). This will trigger the dump.
		if (CONTROLS::IS_CONTROL_JUST_RELEASED(0, 23)) {
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))
			{
				// Open a file called clothingdump.json in the working directory (should normally be the game install directory).
				std::ofstream out = std::ofstream("clothingdump.json", std::ofstream::out);
				if (out.good())
				{
					// Start JSON
					out << "{\n";

					// Run the dump for both female and male online characters.
					for (int pedIndex = 0; pedIndex < 2; pedIndex++)
					{
						Hash pedHash = GAMEPLAY::GET_HASH_KEY((char*)mpPeds[pedIndex]);
					
						// Wait up to 2.5ms (in 500ms intervals) for the MP model to load.
						const int maxAttempts = 5;
						int attempts = 0;
						bool hasLoaded = false;
						while ((hasLoaded = STREAMING::HAS_MODEL_LOADED(pedHash)) == false && attempts < maxAttempts)
						{
							STREAMING::REQUEST_MODEL(pedHash);
							WAIT(500);
							attempts++;
						}
					
						if(hasLoaded)
						{
							// Set the current player to the MP character model.
							PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), pedHash);

							// Start a JSON object entry using the character model name as the key.
							out << "\t\"" << mpPeds[pedIndex] << "\": {\n";

							// Dump all drawable&texture variations of all components.
							for (int comp = 0; comp < 12; comp++)
							{
								// Get the number of drawables for the current component.
								int drawables = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), comp);

								// Start a JSON object entry using the component name as the key.
								// The object's entries will be indexed by drawable index,
								// and each entry's value will be a mapping of textureIndex:gxtLabel.
								out << "\t\t\"" << pedComponents[comp] << "\": {\n";

								for (int i = 0; i < drawables; i++)
								{
									// Start a JSON object entry using the drawable index as the key.
									out << "\t\t\t\"" << i << "\": {\n";

									// Get the number of texture variations of this drawable.
									int textures = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), comp, i);
									
									// Dump GXT labels for all of this drawable's textures.
									for (int j = 0; j < textures; j++)
									{
										// This will store the data returned by GetShopPedComponent.
										PedComponent data;
										ZeroMemory(&data, sizeof(PedComponent));

										// Get the component hash based on the drawable & texture combination.
										Hash componentHash = DLC1::GET_HASH_NAME_FOR_COMPONENT(PLAYER::PLAYER_PED_ID(), comp, i, j);
										
										// Store the component data in the data struct.
										DLC1::GET_SHOP_PED_COMPONENT(componentHash, reinterpret_cast<Any*>(&data));

										// Write the GXT label for the current drawable texture.
										out << "\t\t\t\t\"" << j << "\": \"" << data.gxt << "\"";
										if (j < textures - 1)
										{
											out << ",";
										}

										out << "\n";
									}

									// Close the current drawable's JSON object.
									out << "\t\t\t}";

									if (i < drawables - 1)
									{
										out << ",";
									}

									out << "\n";
								}

								// Close the current component's JSON object.
								out << "\t\t}";
								if (comp < 11)
								{
									out << ",";
								}

								out << "\n";
							}

							// Close the current MP character's JSON object.
							out << "\t}";
							if (pedIndex != 1)
							{
								out << ",";
							}

							out << "\n";
						}
					}
				
					// Close the root JSON object and write the stream to the file.
					out << "\n}";
					out.close();
				}
			}
		}
		
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
