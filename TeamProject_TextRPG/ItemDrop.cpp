#include "Character.h"
#include "ItemDrop.h"
#include "Random.h"

void ItemDrop::itemDrop(Character* character) {
	
    int itemDropRoll = RandomMt19937<int>(1, 100);
	if (itemDropRoll >= 30) {
        std::cout << "¸ó½ºÅÍ°¡ ¾Æ¹«°Íµµ ¶³¾î¶ß¸®Áö ¾Ê¾Ò½À´Ï´Ù ...\n";
        return;
	}



        struct RawItem {
            std::string type;
            std::string name;
            int value;
            int price;
        };

        RawItem itemDB[10] = {
                { "Health", "¼ÒÇü Ã¼·Â Æ÷¼Ç", 30, 10 },
                { "Health", "ÁßÇü Ã¼·Â Æ÷¼Ç", 60, 25 },
                { "Health", "¿¤¸¯¼­", 100, 60 },
                { "Attack", "ÀüÅõ ÀÚ±ØÁ¦", 5, 20 },
                { "Attack", "ÈûÀÇ ¹°¾à", 10, 40 },
                { "Weapon", "ÆÐµµ±ºÁÖÀÇ °¡½Ã´ë°Ë", 18, 60 },
                { "Weapon", "¿µÈ¥¼öÈ®ÀÚÀÇ ¼­¸®³´", 20, 70 },
                { "Weapon", "Â÷¿ø ¿Ö°îÀÇ Áß·ÂÁöÆÎÀÌ", 50, 200 },
                { "Armor", "Ä¥Èæ±â»ç´Ü Á¤¿¹°©¿Ê", 40, 160 },
                { "Armor", "È²È¥ÀÇ ¹æ¶ûÀÚ °¡Á×ÄÚÆ®", 60, 250 }
        };

        itemDropRoll = RandomMt19937<int>(0, 9);
        RawItem droppedItem = itemDB[itemDropRoll];
        character->getInventory()->AddItem(droppedItem.type, droppedItem.name, droppedItem.value, droppedItem.price);
        std::cout << "¸ó½ºÅÍ°¡ [" << droppedItem.name << "]À»(¸¦) ¶³¾î¶ß·È½À´Ï´Ù ...\n";
}

