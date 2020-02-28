#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <sstream>
#include "acshell/acshell.hpp"
#include <vector>

//using namespace acs;
using namespace std;

string G_layer="";
struct OBJ{
	string id;
	string tag;//tag:{...}, only contains ...
};
struct ItemFormat{
	int Slot;//-1:not using Slot, -2:error
	int Count;//0:not using Count, -1:error
	OBJ item;
};
map<string, OBJ> G_ItemsList;//string->ItemName,OBJ->Item{id<string>, tag<string>}

OBJ CustomItem(int);
string Queue_String2String(queue<string>);
void WriteText2File(string);
void WriteFile(string,queue<string>,string);
int GetMethod();
string TagHelper();
queue<string> shulker_box_items(int);
void disLayer();
OBJ GetItemFromList();
void Save__G_ItemsList__ToFile();
void Load__G_ItemsList__FromFile();
//string WanderingTrader();
string NameCreator(char);
string shulker_box_tag_maker(int);
string CustomItemFormat_noSlot(int,queue<string>,bool);
OBJ EntityMaker(string id);
string RecipeMaker();
string OBJ2OBJFormat(OBJ);
string OBJ2OBJFormat_entity(OBJ);
void READ_data_(string,vector<string>&);

//not done...
void LogError(string);
//better with reference call to load file and save to vector...
//data.Minecraft_Items.txt, data.Minecraft_Entities.txt
void LOAD_SELECTIONS();//&Variable_VectorName, FIleName

//Global Library
vector<string> G_CustomItemsName;
vector<string> menu_seletions={"custom item","shulker box","special entity", "wandering trader", "mob spawner", "entity spawn egg", "save items", "load Fileitems", "Load ItemsList", "control", "help", "exit"};
vector<string> color_selections={"black", "white", "dark_blue", "blue", "dark_green", "green", "dark_aqua", "aqua", "dark_red", "red", "dark_purple", "light_purple", "	gold", "yellow", "dark_gray", "gray"};
vector<string> Tag_Helper_selections={"Enchantments", "Name", "ItemName", "EntityName", "Damage", "RepairCost", "help", "$End"};
vector<string> EntityMaker_selections={"Recipes", "CustomName", "HandItems", "ArmorItems", "HandDropChances", "ArmorDropChances", "Passengers", "help", "$End"};
vector<string> RecipeMaker_selections={"$custom_ItemFormat", "Count:", "id:", "tag:"};
//using function to load...
vector<string> Minecraft_Items;//data.Minecraft_Items.txt
//vector<string> MGMG;//when acshell.cpp library is fixed, willl be change to G_CustomItemsName+Minecraft_Items
vector<string> Minecraft_Entities;//data.Minecraft_Entities.txt
vector<string> Minecraft_Eggs;//data.Minecraft_Spawn_Egg.txt
vector<string> Enchantments_selections={"$END", "aqua_affinity", "bane_of_arthropods", "blast_protection", "channeling", "curse_of_binding", "curse_of_vanishing", "depth_strider", "efficiency", "feather_falling", "fire_aspect", "flame", "fortune", "frost_walker", "impaling", "infinity", "knockback", "looting", "loyalty", "luck_of_the_sea", "lure", "mending", "multishot", "piercing", "power", "projectille_protection", "protection", "punch", "quick_charge", "respiration", "riptide", "sharpness", "chopping", "silk_touch", "smite", "sweeping_edge", "thorns", "unbreaking"};

void READ_data_(string FileName, vector<string> &myVec){
	string text="";
	ifstream myfile;
	myfile.open(FileName);
	while(getline(myfile, text)){
		myVec.push_back(text);
	}
}

void disLayer(){
	if(G_layer.length()>0) G_layer=G_layer.substr(0,G_layer.size()-1);
}

/*
 * Finish
 */
void WriteText2File(string s){
	ofstream myfile;
	myfile.open("output.Minecraft_Command.txt");
	myfile << s;cout << s;
	myfile.close();
}


/*
 * Finish
 */
string Queue_String2String(queue<string> lists){
	string ans="";
	while(!lists.empty()){
		if(ans==""){
			ans = lists.front();
		}else{
			ans=ans+","+lists.front();
		}
		lists.pop();
	}
	return ans;
}

/*
 * Finish
 */
void WriteFile(string head, queue<string> lists, string end){
	ofstream myfile;
	myfile.open ("output.Minecraft_Command.txt");
	myfile << head;cout << head;
	while(!lists.empty()){
		string t = lists.front();
		myfile << t << ',';std::cout << t << ',';
		lists.pop();
	}
	myfile << end;cout << end;
	myfile.close();
}

/*
 * Finish
 */
int GetMethod(){
	cout << "Using In GetItems(_>i) or GiveCommand(_>g) or Both(_>b)\n_>";
	char c;cin >> c;
	if(c=='g'){
		return 1;
	}else if(c=='i'){
		return 2;
	}else if(c=='b'){
		return 3;
	}else{
		cout << "error in using mode select...\n";
	}
}

/*
 * Finish
 */
//we chan create a new error detector function
	//if(results.substr(0,12)=="error code @"){
	//	cout << "\n\n>>>>>\nError Occur::\n\t" << results.substr(13,results.length()-12) << "\n>>>>>\n\n";
	//}else{
	//	
	//}
void LogError(string messages){
	
}


string TagHelper(){
	string tag="";
	//no needs '{' at front or '}' at bottom
	cout << G_layer << "Do you need tag(y/n)\n" << G_layer << ":";
	char c;cin >> c;
	if(c=='y'){
		string s;
		cout << G_layer << "<MODE OPTIONs>\n"
			 << G_layer << "Enchantments\n"
			 << G_layer << "Name(ItemName/EntityName)\n"
			 << G_layer << "Damage\n"
			 << G_layer << "RepairCost\n"
			 << G_layer << "help\n"
			 << G_layer << "$End\n"
			 << G_layer << ":>";
		while(true){
			s = SuperInput(Tag_Helper_selections);
			if(s=="Enchantments"){
				string id, data;int lvl;
				cout << "\n" << G_layer << "id($END:for finish):\"minecraft:";
				while(true){
					id=SuperInput(Enchantments_selections);
					if(id=="$END") break;
					cout << "\n" << G_layer << "lvl:";cin >> lvl;
					data = data + "{id:\"minecraft:"+id+"\",lvl:"+std::to_string(lvl)+"},";
					
					cout << "\n\n" << G_layer << "id:\"minecraft:";
				}
				cout << "\n" << G_layer << "Get Enchantments\n" << G_layer << " (next ?? help) \n" << G_layer << "";
				tag = (tag=="" ? ("Enchantments:["+data+"]"):(tag+",Enchantments:["+data+"]"));
			}else if(s=="Name" || s=="ItemName" || s=="EntityName"){//(both item & entity)
				//no need for adding G_layer
				string results;
				if(s=="Name"){
					results = NameCreator('u');
				}else if(s=="ItemName"){
					results = NameCreator('i');
				}else if(s=="EntityName"){
					results = NameCreator('e');
				}else{
					cout << "\n>>>>>\nerror @ Tag_Helper :: Name\n>>>>>\n";
				}
				tag = (tag=="" ? ("display:{" + results + "}"):(tag+",display:{" + results + "}"));				
			}else if(s=="Damage"){
				string data;
				cout << "\n" << G_layer << "input the damage you want to give to the item.\n" << G_layer << "";int num;cin >> num;
				data = "Damage:"+std::to_string(num);
				cout << "\n" << G_layer << "Get Damage\n" << G_layer << " (next ?? help) \n" << G_layer << "";
				tag = (tag=="" ? (data):(tag+","+data));
			}else if(s=="RepairCost"){
				string data;
				cout << "\n" << G_layer << "How Many Level Should The Repair(in anvil) Take ? \n" << G_layer << "";int num;cin >> num;
				data = "RepairCost:"+std::to_string(num);
				cout << "\n" << G_layer << "Get ReapirCost\n" << G_layer << " (next ?? help) \n" << G_layer << "";
				tag = (tag=="" ? (data):(tag+","+data));
			}else if(s=="help"){
				cout << G_layer << "<MODE OPTIONs>\n"
					 << G_layer << "Enchantments\n"
					 << G_layer << "Name(ItemName/EntityName)\n"
					 << G_layer << "Damage\n"
					 << G_layer << "RepairCost\n"
					 << G_layer << "help\n"
					 << G_layer << "$End\n"
					 << G_layer << ":>";
			}else if(s=="$End"){
				cout << "\n" << G_layer << "tag stored..\n";
				break;
			}else{
				cout << "\n" << G_layer << "no find...\n" << G_layer << "try again!!\n" << G_layer << "";
			}
			/*
			else if(s=="CustomName"){
				string name, data;
				cout << "\n" << G_layer << "What CustomName Will You Like To Call Your 'Entity'\n" << G_layer << "";
				cin.get();getline(cin, name);
				data = "display:{CustomName:\"\\\""+name+"\\\"\"}";
				cout << "\n" << G_layer << "Get CustomName\n" << G_layer << " (next ?? help) \n" << G_layer << "";
				tag = (tag=="" ? (data):(tag+","+data));
			}
			*/
			
			
		}
		
	}
	return tag;
}

queue<string> shulker_box_items(int time){
	cout << G_layer << "Slot id(s)---------\n";
	cout << G_layer << "|00|01|02|03|04|05|06|07|08|\n";
	cout << G_layer << "|09|10|11|12|13|14|15|16|17|\n";
	cout << G_layer << "|18|19|20|21|22|23|24|25|26|\n\n\n";
	
	int Count, Slots[27], Counts[27], Slot_index, Count_index;string sSlot, sCount, item, tag;queue<string> items_list;
	cout << G_layer << "Slot(-1:end funtion)=";cin.get();getline(cin, sSlot);
	while(sSlot!="-1"){
		stringstream ss;ss<<sSlot;Slot_index=0;int a;
		while(ss>>a){
			Slots[(Slot_index==27 ? 0:Slot_index++)] = a;
		}
		cout << G_layer << "item($custom_item)=\"minecraft:";item=SuperInput({Minecraft_Items, G_CustomItemsName});if(item=="$custom_item") cout << G_layer << "got it !!\n";
		cout << G_layer << "Count=";cin.get();getline(cin, sCount);
		stringstream sss;sss<<sCount;Count_index=0;
		while(sss>>a){
			Counts[(Count_index==27 ? 0:Count_index++)] = a;
		}
		if(item=="$custom_item"){
			G_layer=G_layer+"\t";
			OBJ ii = CustomItem(time);
			item=ii.id;
			tag=ii.tag;
			disLayer();
		}else{
			cout << G_layer << "tag($tag_helper or $none)=";cin >> tag;if(tag=="$tag_helper") G_layer=G_layer+"\t",tag=TagHelper(),disLayer();else if(tag=="$none") tag="";
		}
		for(int i=0;i<Slot_index;i++){
			string ans = "{Slot:"+std::to_string(Slots[i])+"b,id:\"minecraft:"+item+"\",Count:"+std::to_string(Counts[i%Count_index])+"b,tag:{"+tag+"}}";
			items_list.push(ans);
		}
		cout << "\n" << G_layer << "Slot=";cin.get();getline(cin, sSlot);
	}
	return items_list;
}

string shulker_box_tag_maker(int time){
	if(time>=3) cout << "\n>>>>>too many(" << time+1 << ") shulker_box in the system, please be careful...\n>>>>>\n";
	
	queue<string> items=shulker_box_items(time);
	string output="{BlockEntityTag:{Items:[";
	while(!items.empty()){
		string t = items.front();
		output = output + t + ",";
		items.pop();
	}
	output = output + "]}}";
	
	//return to tag:{...}
	return output;
}

OBJ CustomItem(int time){
	string item, tag, ItemName;//tag:{...}, without '{' and '}'
	OBJ OBJ_item;bool bb=false;
	
	cout << G_layer << "create a new one(c), or find an old one(f) ?? _>";
	char cc;cin >> cc;
	if(cc=='f'){
		A:
			cout << "ItemName=";ItemName=SuperInput({Minecraft_Items, G_CustomItemsName});//G_CustomItemsName+Minecraft_Items
			while(G_ItemsList.count(ItemName)==0){
				if(ItemName=="$cancel"){
					bb=true;
					goto B;
				}else if(ItemName=="$list"){
					cout << "not yet...\n";
					cout << "ItemName=";
				}else{
					cout << "Item No Found...\n";
					cout << "ItemName($cancel/$list)=";
				}
				cin >> ItemName;
			}
			cout << "\t/> Found Item : " << ItemName << "!!\n\t----------\n";
			cout << "\t   id:" << G_ItemsList[ItemName].id << "\n\t   tag(in {}):" << G_ItemsList[ItemName].tag << "\n\t----------\n";
			cout << "\t/> Select This Item ?? (y/n)_>";char c;cin >> c;
			if(c=='y'){
				return G_ItemsList[ItemName];
			}else{
				goto A;
			}
	}
	
	B:
		//create a new item
		if(bb) cout << G_layer << "'$cancel' recieve, bump to create a new item...\n";
		cout << G_layer << "item=\"minecraft:";cin >> item;
		if(item=="$shulker_box"){
			item="shulker_box";
			G_layer+="\t",tag=shulker_box_tag_maker(time+1),disLayer();
		}else{
			cout << G_layer << "tag($tag_helper or $none)=";cin >> tag;if(tag=="$tag_helper") G_layer=G_layer+"\t",tag=TagHelper(),disLayer();else if(tag=="$none") tag="";
		}
		OBJ_item.id=item;
		OBJ_item.tag=tag;
		
		//store the item to short-memory
		cout << G_layer << "Would You Like To Save This 'custom_item' for a while...(y/n) ?? ";
		char c;cin >> c;
		if(c=='y'){
			cout << G_layer << "Input Name For It(No Space)_>";
			cin >> ItemName;
			while(G_ItemsList.count(ItemName) > 0){
				cout << G_layer << "Name Conflicted, Please Rename It Again\n";
				cout << G_layer << "Input Name For It(No Space)_>";
			}
			//no G_layer, because name may be long...
			cout << "/> Item " << ItemName << " established !!\n----------\n";
			cout << ItemName << "\n\tid(item):" << item << "\n\ttag(in {}):" << tag << "\n----------\n\n";
			G_ItemsList.insert( std::pair<string, OBJ>(ItemName, OBJ_item) );
			G_CustomItemsName.push_back("#"+ItemName);
		}
	
	return OBJ_item;
}

OBJ GetItemFromList(){
	
}

void Save__G_ItemsList__ToFile(){
	//save all stored data to MC_dat file
	//using similar-jsoned format saving data
	
//	{
//		ItemName : "..."
//		Item : 
//		{
//			id : "..."
//			tag : "..."
//		}
//	}

}

void Load__G_ItemsList__FromFile(){
	//load all stored data in MC_dat file to program
	//decode similar-jsoned format to get data
}

//next 1¡Gadd more feature to item selection
	//using "$re_item" can help user select item that is not from "minecraft", but from other mods
	//thus, id will be change from "minecraft:<user_selection>" to "<user_input>:<user_selection>"
//next 2¡Gitem format should be more cautiously determined/defined
	//ItemFormat : (struct)[Slot:_<int>,Count:_<int>,id:_<string>,tag:_<string>]
	//OBJ : (struct)[id:_<string>,tag:_<string>]
	//MobileItemAttacher : "tag:{"+ OBJ||ItemFormat +"}"
	//GiveItemAttacher : id:_<string>+"{"+ OBJ||ItemFormat +"}"

string NameCreator(char name_type){	
	string flag,name,data="",color="white",lore_color,data2="";queue<string> lores;
	char type;bool CanLore=false;
	if(name_type=='u'){
		cout << "\n" << G_layer << "What Is Now Being Created ?? item(i), entity(e)_>";
		cin >> type;
	}else if(name_type=='e' || name_type=='i'){
		type=name_type;
	}
	if(type=='i'){
		cout << "\n" << G_layer << "What Name Will You Like To Call Your 'Item'\n" << G_layer << "_:";
		flag = "Name";
		CanLore=true;
	}else if(type=='e'){
		cout << "\n" << G_layer << "What CustomName Will You Like To Call Your 'Entity'\n" << G_layer << "_:";
		flag = "CustomName";
	}else{
		return "error code @NameCreator() Selected Wrong Name Edit Character";
	}
	cin.get();getline(cin, name);
	cout << "\n" << G_layer << "Would you Like To Change Color(y/n)";
	char c;cin >> c;
	if(c=='y'){
		cout << "\n" << G_layer << "Following Colors Are Recently Available";
		cout << "\n" << G_layer << "black\twhite\n" << G_layer << "gold\tyellow\n";
		cout << "\n" << G_layer << "drak_red\tred\n" << G_layer << "dark_green\tgreen\n";
		cout << "\n" << G_layer << "dark_aqua\taqua" << G_layer << "dark_blue\tblue";
		cout << "\n" << G_layer << "drak_purple\tlight_purple" << G_layer << "dark_gray\tgray\n"<< G_layer << "";
		color=SuperInput(color_selections);
	}
	cout << "\n" << G_layer << "Would you Like To Have Strong Name(reduce chance to failed...)(y/n)";
	char c1;cin >> c1;
	if(c1=='y' || c=='y'){
		data = flag+":\"{\\\"text\\\":\\\""+name+"\\\",\\\"color\\\":\\\""+color+"\\\"}\"";
	}else{
		data = flag+":\"\\\""+name+"\\\"\"";
	}
	cout << "\n" << G_layer << "Get " << flag << "\n" << G_layer;
	
	if(type=='i'){
		cout << "\n" << G_layer << "Would you Like To Add Explainations To Items(y/n)";
		char c2;cin >> c2;cin.get();
		if(c2=='y'){
			cout << "\n" << G_layer << "------Start------\n" << G_layer << "($end$ to end)" << G_layer << "(no \" in word please!!)\n" << G_layer << "";
			string text;getline(cin, text);
			while(text!="$end$"){
				lores.push(text);
				cout << "\n" << G_layer << "";
				getline(cin, text);
			}
			cout << "\n" << G_layer << "------$end$------\n" << G_layer << "Lores Get";
			cout << "\n\n" << G_layer << "Would you Like To Change Color To Explainations(y/n)";
			char c3;cin >> c3;
			if(c3=='y'){
				cout << "\n" << G_layer << "Following Colors Are Recently Available";
				cout << "\n" << G_layer << "black\twhite\n" << G_layer << "dark_blue\tblue";
				cout << "\n" << G_layer << "dark_green\tgreen\n" << G_layer << "dark_aqua\tauqa";
				cout << "\n" << G_layer << "drak_red\tred\n" << G_layer << "drak_purple\tlight_purple";
				cout << "\n" << G_layer << "gold\tyellow\n" << G_layer << "dark_gray\tgray\n\t";
				
				data2 = "Lore:[";
				while(!lores.empty()){
					std::cout << "\n" << G_layer << "Color For This Line @"+lores.front()+"\n" << G_layer << "" << G_layer << "@_>";cin >> lore_color;cout << "" << G_layer << "###";
					data2 = data2 + "\"{\\\"color\\\":\\\""+lore_color+"\\\",\\\"text\\\":\\\""+lores.front()+"\\\"}\",";
					lores.pop();
				}
				data2 = data2 + "]";
			}else{
				data2 = "Lore:[";
				while(!lores.empty()){
					data2 = data2 + "\\\"" + lores.front() + "\\\",";
					lores.pop();
				}
				data2 = data2 + "]";
			}
		}
		cout << "\n" << G_layer << "Get Lore\n" << G_layer << " (next ?? help) \n" << G_layer;
	}
	//return to display:{...}
	string debug=((CanLore) ? (data+","+data2):(data));
	cout << "##243" << debug << "void{" << data2 << "}" << endl;
	return debug;
}

//please make sure that the chat_message amount is equal to the amount, or may encounter error ??
string CustomItemFormat_noSlot(int amount,queue<string> chat, bool show__G_layer){
	string datas="",data="";int Count;
	for(int i=0;i<amount;i++){
		if(show__G_layer) cout << G_layer;cout << "-----<hint>:" << chat.front() << "-----\n";chat.pop();
		cout << G_layer << "Count(Of This Item)_>";cin >> Count;
		OBJ obj = CustomItem(0);
		data = (obj.tag=="" ? ("{Count:"+std::to_string(Count)+"b,id:"+obj.id+"}"):("{Count:"+std::to_string(Count)+"b,id:"+obj.id+",tag:{"+obj.tag+"}}"));
		datas = (datas=="" ? (data) : (datas+","+data));
		cout << '\n' << G_layer;
	}
	//return {Count:_,id:_,tag:_},{Count:_,id:_,tag:_},...
	return datas;
}

OBJ EntityMaker(string identity){
	string s,datas,id=identity;bool NeedRecipe;
	if(identity=="") cout << G_layer << "Which Entity Is Choosen ? _>", id=SuperInput(Minecraft_Entities);
	if(id=="villager" || id=="wandering_trader") NeedRecipe=true;
	
	cout << "\n" << G_layer << "-------Start Edit-------";
	if(NeedRecipe) cout << "\n" << G_layer << "Recipes";
	cout << "\n" << G_layer << "CustomName"
		 << "\n" << G_layer << "HandItems"
		 << "\n" << G_layer << "HandDropChances"
		 << "\n" << G_layer << "ArmorItems"
		 << "\n" << G_layer << "ArmorDropChances"
		 << "\n" << G_layer << "Passengers"
		 << "\n" << G_layer << "help"
		 << "\n" << G_layer << "$End\n\n\n" << G_layer << "_>";
	s=SuperInput(EntityMaker_selections);
	while(s!="$End"){
		if(s=="Recipes"){
			if(NeedRecipe){
				string data = RecipeMaker();
				datas = (datas=="" ? (data):(datas+","+data));
			}else{
				cout << "\n\n>>>>>\nOnly Villager And Trader Can Obtain Recipes\n>>>>>\n";
				cout << "\n" << G_layer << "CustomName"
					 << "\n" << G_layer << "HandItems"
					 << "\n" << G_layer << "HandDropChances"
					 << "\n" << G_layer << "ArmorItems"
					 << "\n" << G_layer << "ArmorDropChances"
					 << "\n" << G_layer << "help\n"
					 << "\n" << G_layer << "$End\n";
			}
			cout << "\n" << G_layer << "\nRecipes Get !! (next ?? help)\n" << G_layer;
		}else if(s=="CustomName"){
			//string name = "display:{"+NameCreator('e')+"}";
			string name = NameCreator('e');
			datas = (datas=="" ? (name):(datas+","+name));
			cout << "\n" << G_layer << "\nCustomName Get !! (next ?? help)\n" << G_layer;
		}else if(s=="ArmorItems"){
			queue<string> chats;chats.push("boots");chats.push("leggings");chats.push("chestplate");chats.push("helmet");
			string data="ArmorItems:["+CustomItemFormat_noSlot(4,chats,true)+"]";
			datas = (datas=="" ? (data):(datas+","+data));
			cout << "\n" << G_layer << "\nArmorItems Get !! (next ?? help)\n" << G_layer;
		}else if(s=="HandItems"){
			queue<string> chats;chats.push("right_hand");chats.push("left_hand");
			string data="HandItems:["+CustomItemFormat_noSlot(2,chats,true)+"]";
			datas = (datas=="" ? (data):(datas+","+data));
			cout << "\n" << G_layer << "\nHandItems Get !! (next ?? help)\n" << G_layer;
		}else if(s=="ArmorDropChances"){
			cout << "Nomal Drop Chance:0.085\n";float a, b, c, d;
			cout << G_layer << "boot:";cin >> a;cout << G_layer << "leggings:";cin >> b;
			cout << G_layer << "chestplate:";cin >> c;cout << G_layer << "helmet:";cin >> d;
			string data="ArmorDropChances:["+std::to_string(a)+std::to_string(b)+std::to_string(c)+std::to_string(d)+"]";
			datas = (datas=="" ? (data):(datas+","+data));
			cout << "\n" << G_layer << "\nArmorDropChances Get !! (next ?? help)\n" << G_layer;
		}else if(s=="HandDropChances"){
			cout << "Nomal Drop Chance:0.085\n";float a, b;
			cout << G_layer << "right_hand:";cin >> a;cout << G_layer << "left_hand:";cin >> b;
			string data="HandDropChances:["+std::to_string(a)+"f,"+std::to_string(b)+"f]";
			datas = (datas=="" ? (data):(datas+","+data));
			cout << "\n" << G_layer << "\nHandDropCHances Get !! (next ?? help)\n" << G_layer;
		}else if(s=="Passengers"){
			cout << "[{id:_,tag:_},{id:_,tag:_}]\n";
			string passengers="", head="Passengers:[", end="]";
			cout << G_layer << "How Many Passenger Are There For " << id << "?? _>";int index=0, count;cin >> count;
			G_layer+="\t";
			while(index!=count){
				passengers = passengers=="" ? OBJ2OBJFormat(EntityMaker("")) : passengers+", "+OBJ2OBJFormat(EntityMaker(""));
				index++;
			}
			disLayer();
			string data = head+passengers+end;
			datas = (datas=="" ? (data):(datas+"@,@"+data));
			cout << "\n" << G_layer << "\nPassengers Get !! (next ?? help)\n" << G_layer;
		}else if(s=="help"){
			cout << "\n" << G_layer << "-------$$-------";
			if(NeedRecipe) cout << "\n" << G_layer << "Recipes";
			cout << "\n" << G_layer << "CustomName"
				 << "\n" << G_layer << "HandItems"
				 << "\n" << G_layer << "HandDropChances"
				 << "\n" << G_layer << "ArmorItems"
				 << "\n" << G_layer << "ArmorDropChances"
				 << "\n" << G_layer << "help"
				 << "\n" << G_layer << "$End\n\n\n" << G_layer << "_>";
		}else{
			cout << G_layer << "Wrong Mode\n" << G_layer << "please, retype it...\n" << G_layer;
		}
		s=SuperInput(EntityMaker_selections);
	}
	OBJ entity;entity.id=id;entity.tag=datas;
	return entity;
}

string RecipeMaker(){
	int maxUses, xp;string item1, item2, item3, recipe_content;queue<string> recipes;
	cout << "\n";
	cout << G_layer << "---$Transactions List$---\n";
	cout << G_layer << "----- ------   ------\n";
	cout << G_layer << "|buy|+|buyB|-->|sell|\n";
	cout << G_layer << "----- ------   ------\n\n";
	cout << '\n' << G_layer << "Now We Will Use 'Item Format' to determine which item to trade,\n" << G_layer << "\t{Count:_,id:_,tag:_}\n";
	cout << G_layer << "And Now We Will Use This Structure For EVER Trade,\n" << G_layer << "\t{maxUses:_int_,buy:_'Item Format'_,buyB:_'Item Format'_,sell:_'Item Format'_,xp:_int_}\n";
	cout << "\n\n";
	
	cout << G_layer << "maxUses(<=0:end function)=";cin >> maxUses;
	while(maxUses>0){
		cout << G_layer << "exp=";cin >> xp;
		queue<string> chat1, chat2, chat3;chat1.push("buy");chat2.push("buyB");chat3.push("sell");
		//{Count:_,id:_,tag:_}
		cout << "\n" << G_layer << "Now Need 'ItemFormat'\n";
		cout << G_layer << "<buy>($custom_ItemFormat):";item1=SuperInput(RecipeMaker_selections);if(item1=="$custom_ItemFormat") cout << G_layer << "Got it!!\n",G_layer+="\t",item1=CustomItemFormat_noSlot(1,chat1,true),disLayer();
		cout << G_layer << "<buyB>($custom_ItemFormat):";item2=SuperInput(RecipeMaker_selections);if(item2=="$custom_ItemFormat") cout << G_layer << "Got it!!\n",G_layer+="\t",item2=CustomItemFormat_noSlot(1,chat2,true),disLayer();
		cout << G_layer << "<sell>($custom_ItemFormat):";item3=SuperInput(RecipeMaker_selections);if(item3=="$custom_ItemFormat") cout << G_layer << "Got it!!\n",G_layer+="\t",item3=CustomItemFormat_noSlot(1,chat3,true),disLayer();
		
		recipe_content = "{maxUses:"+std::to_string(maxUses)+",buy:"+item1+",buyB:"+item2+",sell:"+item3+",xp:"+std::to_string(xp)+"}";
		recipes.push(recipe_content);
		cout << "\n\n" << G_layer << "maxUses(<=0:end function)=";cin >> maxUses;
	}
	return "Offers:{Recipes:["+Queue_String2String(recipes)+"]}";
}

string OBJ2OBJFormat(OBJ obj){
	return "{id:"+obj.id+",tag:{"+obj.tag+"}}";
}

string OBJ2OBJFormat_entity(OBJ obj){
	return "{id:"+obj.id+","+obj.tag+"}";
}

//*1.
//we can make shulker_box function one more big upgrade...
	//change
//Slot:<int>
	//to
//Slot:<string>(using getline(cin,s) & stringstream to deal with a bounch of numbers)

//*2.
//No Matter What Item Format IS Needed...
//#<custom_item_name> can call the function::ItemFastFind() to deal with all type of Items
//	allow user to answer the only neccessary left questions...

int main(){
	//load data.<filename>.txt to vector
	READ_data_("data.Minecraft_Items.txt", Minecraft_Items);
	READ_data_("data.Minecraft_Entities.txt", Minecraft_Entities);
	READ_data_("data.Minecraft_Spawn_Egg.txt", Minecraft_Eggs);
				
	//string flag_for_fun={"--Minecraft_Command_Helper{did_you_just_break_my_code_!?}--","--Minecraft_Command_Helper{Wow!!Me_Too!!ShulkerBox_Is_The_Best}--"};
	string s;int pass;
	cout << "<MODE OPTIONS>\ncustom item\nshulker box\nspecial entity\nwandering trader\nmob spawner\nentity spawn egg\n\n_>";
	s=SuperInput(menu_seletions);
	while(s!="exit"){
		if(s=="") goto CC_end;
		pass=0;
		if(s=="shulker box"){
			string head, end;
			int aa = GetMethod();
			if(aa==1){//GiveCommand
				head = "/give @p shulker_box{BlockEntityTag:{Items:[";
				end = "]}}";
				WriteFile(head, shulker_box_items(0), end);
			}else if(aa==2){//Items
				head = "{Count:1, id:\"minecraft:shulker_box\", tag:{BlockEntityTag:{Items:[";
				end = "]}}}";
				WriteFile(head, shulker_box_items(0), end);
			}else if(aa==3){//both
				string result = "["+Queue_String2String(shulker_box_items(0))+"]";
				string a="/give @p shulker_box{BlockEntityTag:{Items:"+result+"}}";
				string b="{Count:1, id:\"minecraft:shulker_box\", tag:{BlockEntityTag:{Items:"+result+"}}}";
				WriteText2File(a+"\n\n\n"+b);
			}else{
				
			}
			pass=1;
		}else if(s=="custom item"){
			CustomItem(0);
			pass=1;
		}else if(s=="wandering trader"){
			string head = "/summon minecraft:wandering_trader ~ ~ ~ {", end="}";
			string text;
			G_layer+="\t", text = EntityMaker("wandering_trader").tag, disLayer();
			WriteText2File(head+text+end);
		}else if(s=="mob spawner"){
			string head = "/give @p minecraft:spawner{BlockEntityTag:{SpawnData:", mid = ", SpawnPotentials:[{Entity:", end = "}]}}";OBJ obj;
			G_layer+="\t", obj = EntityMaker(""), disLayer();
			WriteText2File(head+OBJ2OBJFormat_entity(obj)+mid+OBJ2OBJFormat_entity(obj)+end);
		}else if(s=="entity spawn egg"){
			string head = "/give @p ", mid="{EntityTag:", end="}", egg;OBJ obj;
			cout << "\tWhich Egg You Want 2 Use??_>";egg=SuperInput(Minecraft_Eggs);
			G_layer+="\t", obj = EntityMaker(""), disLayer();
			WriteText2File(head+egg+mid+OBJ2OBJFormat_entity(obj)+end);
		}else if(s=="special entity"){
			string head = "/summon minecraft:", mid=" ~ ~ ~ {", end="}";
			string text,id;bool flag=false;OBJ obj;
			
//			cout<<"Which Entity Is Choosen ? _>";cin >> id;
//			if(id=="villager" || id=="wandering_trader") flag=true;

			G_layer+="\t", obj = EntityMaker(""), disLayer();
			WriteText2File(head+obj.id+mid+obj.tag+end);
		}else if(s=="help"){
			cout << "\n\n<MODE OPTIONS>\ncustom item\nshulker box\nspecial entity\nwandering trader\nmob spawner\nentity spawn egg\n\n_>";
			cout << "<COMMAND OPTIONs>\nsave items(custom_items)\nload Fileitems(custom_items)\nLoad ItemsList\nhelp\ncontrol\nexit\n_>";
		}else if(s=="save items"){
			cout << "Not Invented Yet...\n";
			continue;s="";
			Save__G_ItemsList__ToFile();
		}else if(s=="load Fileitems"){
			cout << "Custom Items(c)//Minecraft Items(m)\n";
			char c;cin >> c;
			if(c=='c'){
				cout << "Not Invented Yet...\n";
				continue;s="";
				Load__G_ItemsList__FromFile();
			}else if(c=='m'){
				READ_data_("data.Minecraft_Items.txt", Minecraft_Items);
				READ_data_("data.Minecraft_Entities.txt", Minecraft_Entities);
				READ_data_("data.Minecraft_Spawn_Egg.txt", Minecraft_Eggs);
			}else{
				
			}
		}else if(s=="Load ItemsList"){
			cout << "Not Invented Yet...\n";
			continue;s="";
			//show all the G_ItemsList to user
		}else if(s=="exit"){
			return 0;
		}else if(s=="control"){
			queue<string> chat_message;
			chat_message.push("Most Of The Time, 'help' command can help you find out where are you now...");
			chat_message.push("Making A shulker box Is Not EASY...  Thus, At 'Slot:' inputs, you can just type a long number list(no more than 27, and no \"-1\" included) of slot place to store same items\n\t\t'Count' have same funtion, and will correspond with each index(play for it..)");
			chat_message.push("Shulker Box Selection in main menu is the very first function(i just can fix it(remain its look~~)), thus, in fact, in $custom_item Selection can provide better result");
			chat_message.push("In Most Of The Places, 'tab' can make your typing easier");
			chat_message.push("Using PageUp/Down Can Change The Suggestion(blue)");
			chat_message.push("In Any Place, Mentioned To 'item', You Can Use '#'+'<custom_item_name>' to fast load your custom item(won't mention what it is)\tsystem will automatically convert the right format for you, and only ask you the rest neccessary unknown value");
			
			chat_message.push("This Application Is Invented For MineCraft Lover, thus, it is not created for 'reverse-engineering', please don't try to break it...");
			chat_message.push("Because The Program Is Not Strong Enough To Prevent Typing Error<type error> or Revise The Latest Typo In Anywhere, please make sure you look nicely and understand what is asked to input");
			chat_message.push("Maybe somday, if program was updated, we can help you fix the typo(last input) or error tag...");
			chat_message.push("If you have better idea to make the application better, please don't dial us, just do it, share( maybe?? ) it, and make the world better");
			chat_message.push("We hope people who is capable of turning the application's functions to website version appears, then ,maybe, can help more people without this program");
			
			cout << "\n\n\n\n\n\n\n\n/>Here! The Followings Are Available Constuctions\n";
			for(int i=1;i<=6;i++) cout << "\t(" << i << ".) >> " << chat_message.front() << "\n",chat_message.pop();
			cout << "\n/>Here! The Followings Are Rules & Reminders\n";
			for(int i=7;i<=11;i++) cout << "\t(" << i << ".) >> " << chat_message.front() << "\n",chat_message.pop();
			cout << "\n\n\n\n\n\n\n\n_>";
		}else{
			cout << "wrong mode:\n\t\"" << s << "\" not found\n";
		}
		
		if(pass==1){
			cout << "\ndata has been written to \"output.Minecraft_Command.txt\" file\n";
		}else if(pass==-1){
			cout << "\nError Has Occur !!\n";
		}
		
		cout << "\n\n\nProgram Reloaded...\nReady For Input(help?)";
		CC_end:
			cout << "\n_>";
			s=SuperInput(menu_seletions);
	}
	
}
