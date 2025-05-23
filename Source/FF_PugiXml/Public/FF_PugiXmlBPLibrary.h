#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FF_PugiXML_Includes.h"
#include "FF_PugiXmlBPLibrary.generated.h"

using namespace pugi;

USTRUCT()
struct FF_PUGIXML_API FPugiXmlDoctypeAttributes
{
	GENERATED_BODY()

public:

	FString Element_Name = "";
	FString Attribute_Name = "";

};

UCLASS(BlueprintType)
class FF_PUGIXML_API UFFPugiXml_Node : public UObject
{
	GENERATED_BODY()

public:

	xml_node Node;

};

UCLASS(BlueprintType)
class FF_PUGIXML_API UFFPugiXml_Doc : public UObject
{
	GENERATED_BODY()

public:

	xml_document Document;
	
	UPROPERTY(BlueprintReadWrite)
	UFFPugiXml_Node* SchemeElement = nullptr;

};

UCLASS()
class UFF_PugiXmlBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Open Document from File", Keywords = "pugixml, xml, document, open, file"), Category = "Frozen Forest|FF_PugiXml|Open")
	static FF_PUGIXML_API bool PugiXml_Doc_Open_File(UFFPugiXml_Doc*& Out_Doc, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Open Document from Memory", Keywords = "pugixml, xml, document, open, memory"), Category = "Frozen Forest|FF_PugiXml|Open")
	static FF_PUGIXML_API bool PugiXml_Doc_Open_Memory(UFFPugiXml_Doc*& Out_Doc, TArray<uint8> In_Buffer);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Open Document from String", Keywords = "pugixml, xml, document, open, string"), Category = "Frozen Forest|FF_PugiXml|Open")
	static FF_PUGIXML_API bool PugiXml_Doc_Open_String(UFFPugiXml_Doc*& Out_Doc, FString In_String);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Print Document", Keywords = "pugixml, xml, document, print"), Category = "Frozen Forest|FF_PugiXml|Save")
	static FF_PUGIXML_API bool PugiXml_Doc_Print(FString& Out_String, UFFPugiXml_Doc* In_Doc);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Save Document as Buffer", Tooltip = "", Keywords = "pugixml, xml, document, save, buffer, memory, bytes"), Category = "Frozen Forest|FF_PugiXml|Save")
	static FF_PUGIXML_API bool PugiXml_Doc_Save_Memory(TArray<uint8>& Out_Bytes, UFFPugiXml_Doc* In_Doc);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Save Document as File", Tooltip = "", Keywords = "pugixml, xml, document, save, file"), Category = "Frozen Forest|FF_PugiXml|Save")
	static FF_PUGIXML_API bool PugiXml_Doc_Save_File(UFFPugiXml_Doc* In_Doc, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Create Document", Tooltip = "", Keywords = "pugixml, xml, document, create"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API void PugiXml_Doc_Create(UFFPugiXml_Doc*& Out_Doc, FString RootName, bool bIsStandalone);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Clear XML", Tooltip = "", Keywords = "pugixml, xml, document, empty, delete, remove, clear"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Doc_Clear(UPARAM(ref)UFFPugiXml_Doc*& In_Doc);

	/**
	* ADVANCED !
	* DOCTYPE has to be only one in an XML and it's parent has to be directly document's itself.
	* Function automatically check if there is a DOCTYPE in XML or not. If there is, it returns false.
	* @param Out_Nodes This array contains three nodes. DTD delimiter, DOCTYPE, XML delimiter.
	* @param CustomDefinition Function automatically adds <!DOCTYPE Name [ ... ]> you have to fill inside (ELEMENT and/or ATTLIST) yourself.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Custom Doctype", Keywords = "pugixml, xml, document, node, add, doctype, custom"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_Doctype_Custom(TArray<UFFPugiXml_Node*>& Out_Nodes, UFFPugiXml_Doc* In_Doc, FString DoctypeName, FString CustomDefinition);

	/**
	* ADVANCED !
	* DOCTYPE has to be only one in an XML and it's parent has to be directly document's itself.
	* Function automatically check if there is a DOCTYPE in XML or not. If there is, it returns false.
	* If you want to use this, use this only after adding all your stuffs to the XML.
	* @param Out_Nodes This array contains three nodes. DTD delimiter, DOCTYPE, XML delimiter.
	* @param bAddAttributes If you want to add attributes to the DTD list, check this true. But you must NOT USE any non-characters/symbols in attributes values.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Auto Doctype", Keywords = "pugixml, xml, document, node, add, doctype, auto"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_Doctype_Auto(TArray<UFFPugiXml_Node*>& Out_Nodes, UFFPugiXml_Doc* In_Doc, FString DoctypeName, bool bAddAttributes);

	/**
	* @param Parent_Node (Optional and can be nullptr): If this is nullptr, added node will be direct chil of root or scheme element (if it is valid.)
	* @param Anchor_Node (Optional and can be nullptr): This should be one of children of "Parent Node" and you should use it only if you want to use "insert" features.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Node Element", Keywords = "pugixml, xml, document, node, add, element", AutoCreateRefTerm = "In_Attributes"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_Element(UFFPugiXml_Node*& Out_Node, EPugiXmlAddTypes AddType, UFFPugiXml_Doc* In_Doc, UFFPugiXml_Node* Parent_Node, UFFPugiXml_Node* Anchor_Node, FString NodeName, FString NodeValue, const TMap<FString, FString>& In_Attributes);

	/**
	* @param Parent_Node (Optional and can be nullptr): If this is nullptr, added node will be direct chil of root or scheme element (if it is valid.)
	* @param Anchor_Node (Optional and can be nullptr): This should be one of children of "Parent Node" and you should use it only if you want to use "insert" features.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Node Comment", Keywords = "pugixml, xml, document, node, add, comment"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_Comment(UFFPugiXml_Node*& Out_Node, EPugiXmlAddTypes AddType, UFFPugiXml_Doc* In_Doc, UFFPugiXml_Node* Parent_Node, UFFPugiXml_Node* Anchor_Node, FString In_Comment);

	/**
	* @param Parent_Node (Optional and can be nullptr): If this is nullptr, added node will be direct chil of root or scheme element (if it is valid.)
	* @param Anchor_Node (Optional and can be nullptr): This should be one of children of "Parent Node" and you should use it only if you want to use "insert" features.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Node Processing Instructions", Keywords = "pugixml, xml, document, node, add, pi, processing, instructions"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_Pi(UFFPugiXml_Node*& Out_Node, EPugiXmlAddTypes AddType, UFFPugiXml_Doc* In_Doc, UFFPugiXml_Node* Parent_Node, UFFPugiXml_Node* Anchor_Node, FString NodeName, FString NodeValue);

	/**
	* @param Parent_Node (Optional and can be nullptr): If this is nullptr, added node will be direct chil of root or scheme element (if it is valid.)
	* @param Anchor_Node (Optional and can be nullptr): This should be one of children of "Parent Node" and you should use it only if you want to use "insert" features.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Node Plain Character", Keywords = "pugixml, xml, document, node, add, pcdata, plain, character"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_pcdata(UFFPugiXml_Node*& Out_Node, EPugiXmlAddTypes AddType, UFFPugiXml_Doc* In_Doc, UFFPugiXml_Node* Parent_Node, UFFPugiXml_Node* Anchor_Node, FString Value);

	/**
	* @param Parent_Node (Optional and can be nullptr): If this is nullptr, added node will be direct chil of root or scheme element (if it is valid.)
	* @param Anchor_Node (Optional and can be nullptr): This should be one of children of "Parent Node" and you should use it only if you want to use "insert" features.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Add Node CDATA", Keywords = "pugixml, xml, document, node, add,  cdata"), Category = "Frozen Forest|FF_PugiXml|Write")
	static FF_PUGIXML_API bool PugiXml_Node_Add_cdata(UFFPugiXml_Node*& Out_Node, EPugiXmlAddTypes AddType, UFFPugiXml_Doc* In_Doc, UFFPugiXml_Node* Parent_Node, UFFPugiXml_Node* Anchor_Node, FString Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Get Direct Children", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, direct"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Children_Direct(TArray<UFFPugiXml_Node*>& Out_Children, UObject* Target_Object);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Get Children Recursive", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, all, recursive"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Children_Recursive(TArray<UFFPugiXml_Node*>& Out_Children, UObject* Target_Object);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Get Border Children", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, first, last, border"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Children_Border(UFFPugiXml_Node*& Out_Child, UObject* Target_Object, bool bIsLast);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Get Siblings", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, sibling"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Siblings(UFFPugiXml_Node*& Out_Sibling, UFFPugiXml_Node* Target_Node, bool bIsPrevious);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Find Child by Name", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, find, by, name"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Find_Child_By_Name(UFFPugiXml_Node*& Out_Sibling, UObject* Target_Object, FString Child_Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Find Child by Attribute", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, child, children, find, by, attribute"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Find_Child_By_Attribute(UFFPugiXml_Node*& Out_Sibling, UObject* Target_Object, FString Attribute_Name, FString Attribute_Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Find Parent", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, parent, find"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Find_Parent(UFFPugiXml_Node*& Found_Parent, bool& bIsParentXml, UFFPugiXml_Node* Target_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Get Name", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, name"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Name(FString& Out_Name, UFFPugiXml_Node* Target_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Get Value", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, value"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Value(FString& Out_Value, UFFPugiXml_Node* Target_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Get Attributes", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, attribute, attributes"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Attributes(TMap<FString, FString>& Out_Attributes, UFFPugiXml_Node* Target_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Get Attribute Value", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, attribute, value"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Attribute_Value(FString& Out_Value, UFFPugiXml_Node* Target_Node, FString In_Attribute_Name);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Get Type", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, type"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Get_Type(EPugiXmlDataTypes& Out_Types, UFFPugiXml_Node* Target_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Check If Empty", Tooltip = "", Keywords = "pugixml, xml, document, get, node, read, check, empty"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Check_Empty(bool& bIsEmpty, UObject* Target_Object);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Compare Nodes", Tooltip = "", Keywords = "pugixml, xml, document, get, node, compare"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Compare_Nodes(bool& bAreTheySame, UFFPugiXml_Node* First_Node, UFFPugiXml_Node* Second_Node);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Pugixml - Compare Documents", Tooltip = "", Keywords = "pugixml, xml, document, get compare"), Category = "Frozen Forest|FF_PugiXml|Parse")
	static FF_PUGIXML_API bool PugiXml_Compare_XML(bool& bAreTheySame, UFFPugiXml_Doc* First_Document, UFFPugiXml_Doc* Second_Document);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Set Name", Tooltip = "", Keywords = "pugixml, xml, document, set, node, read, name"), Category = "Frozen Forest|FF_PugiXml|Edit")
	static FF_PUGIXML_API bool PugiXml_Set_Name(UFFPugiXml_Node* Target_Node, FString In_Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Set Value", Tooltip = "", Keywords = "pugixml, xml, document, set, node, read, value"), Category = "Frozen Forest|FF_PugiXml|Edit")
	static FF_PUGIXML_API bool PugiXml_Set_Value(UFFPugiXml_Node* Target_Node, FString In_Value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Set Attributes", Tooltip = "", Keywords = "pugixml, xml, document, set, add, node, read, attribute, attributes", AutoCreateRefTerm = "In_Attributes"), Category = "Frozen Forest|FF_PugiXml|Edit")
	static FF_PUGIXML_API bool PugiXml_Set_Attributes(UFFPugiXml_Node* Target_Node, bool bAddToStart, const TMap<FString, FString>& In_Attributes);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Remove Node 1", Tooltip = "It has to be direct child/parent not grand-children.", Keywords = "pugixml, xml, document, node, remove"), Category = "Frozen Forest|FF_PugiXml|Edit")
	static FF_PUGIXML_API bool PugiXml_Node_Remove_1(UPARAM(ref)UObject*& Source, UPARAM(ref)UFFPugiXml_Node*& Delete_Target);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pugixml - Remove Node 2", Tooltip = "It automatically finds parent.", Keywords = "pugixml, xml, document, node, remove"), Category = "Frozen Forest|FF_PugiXml|Edit")
	static FF_PUGIXML_API bool PugiXml_Node_Remove_2(UPARAM(ref)UFFPugiXml_Node*& Delete_Target);

};