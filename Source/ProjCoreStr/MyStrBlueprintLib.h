#pragma once

#include "MyStrBlueprintLib.generated.h"

UCLASS()
class UMyStrBlueprintLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void DoAll();

	UFUNCTION(BlueprintCallable)
	static void ConvertToCString();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_CString();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_FText();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_FName();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_NameFrom_CString();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_FStringFrom_CString();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_FTextFrom_CString();

	UFUNCTION(BlueprintCallable)
	static void DoConstruct_FTextFrom_Literal();

	UFUNCTION(BlueprintCallable)
	static void DoLengthEmpty();

	UFUNCTION(BlueprintCallable)
	static void TransformToString();

	UFUNCTION(BlueprintCallable)
	static void DoCopy();

	UFUNCTION(BlueprintCallable)
	static void DoLog();

	UFUNCTION(BlueprintCallable)
	static void DoFormat();

	UFUNCTION(BlueprintCallable)
	static void DoPrintf();

	UFUNCTION(BlueprintCallable)
	static void DoIterator();

	UFUNCTION(BlueprintCallable)
	static void DoIndex();

	UFUNCTION(BlueprintCallable)
	static void DoPattern();

	UFUNCTION(BlueprintCallable)
	static void DoPath();

	UFUNCTION(BlueprintCallable)
	static void DoResizeReserve();

	UFUNCTION(BlueprintCallable)
	static void DoReplace();

	UFUNCTION(BlueprintCallable)
	static void DoRemove();

	UFUNCTION(BlueprintCallable)
	static void DoAppend();

	UFUNCTION(BlueprintCallable)
	static void DoInsert();

	UFUNCTION(BlueprintCallable)
	static void DoFind();

	UFUNCTION(BlueprintCallable)
	static void DoSubstring();

	UFUNCTION(BlueprintCallable)
	static void DoLeftRightMid();

	UFUNCTION(BlueprintCallable)
	static void DoCase();

	UFUNCTION(BlueprintCallable)
	static void DoParse();

	UFUNCTION(BlueprintCallable)
	static void DoParse_Int_Atoi();

	UFUNCTION(BlueprintCallable)
	static void DoParse_Int();

	UFUNCTION(BlueprintCallable)
	static void DoParse_Float();

	UFUNCTION(BlueprintCallable)
	static void DoParse_Float_Atof();

	UFUNCTION(BlueprintCallable)
	static void DoSerialize();

	UFUNCTION(BlueprintCallable)
	static void DoMiscRange();

	UFUNCTION(BlueprintCallable)
	static void DoMisc();

	UFUNCTION(BlueprintCallable)	
	static void DoTest();

private:
	UFUNCTION(BlueprintPure)
	static FString YesNo(bool bYes);
};