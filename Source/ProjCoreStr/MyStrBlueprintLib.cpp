#include "MyStrBlueprintLib.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

#include "Misc/CString.h" // For FCString::Atoi, FCString::Atof
#include "Misc/DefaultValueHelper.h"
#include "Misc/Parse.h"

#include "Misc/Paths.h" // FPaths - Path helpers

#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLibLog, Log, All);
DEFINE_LOG_CATEGORY(MyLibLog);

/**
* WARNING!!! Namespace definition: that's why we will be able to call LOCTEXT
*/
#define LOCTEXT_NAMESPACE "MyStrBlueprintLib"

TArray<uint8> MyCreateRandomByteArray(int32 InSize)
{
	check(InSize > 0);

	TArray<uint8> Result;
	Result.SetNumUninitialized(InSize);
	for(int32 Index = 0; Index < Result.Num(); ++Index)
	{
		Result[Index] = static_cast<uint8>(FMath::RandRange(0, 255));
	}
	return Result;
}

void UMyStrBlueprintLib::DoAll()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoAll"));
	DoLengthEmpty();
	ConvertToCString();
	DoConstruct_CString();
	DoConstruct_FText();
	DoConstruct_FName();
	DoCopy();
	DoLog();
	DoFormat();	
	DoPrintf();
	DoIterator();
	DoIndex();
	DoPattern();
	DoPath();
	DoResizeReserve();
	DoReplace();
	DoRemove();
	DoAppend();
	DoInsert();
	DoFind();
	DoSubstring();
	DoLeftRightMid();
	DoCase();
	DoParse();
	DoSerialize();
	DoMiscRange();
	DoMisc();
	DoTest();
}

void UMyStrBlueprintLib::DoLengthEmpty()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoLengthEmpty..."));

	{
		static FName const TestNameEmpty { TEXT(""), FNAME_Add };
		bool const bEmpty_IsNone = TestNameEmpty.IsNone();
	
		static FName const TestNameNone { TEXT("None"), FNAME_Add };
		bool const bTestNameNone_IsNone = TestNameNone.IsNone();

		static FName const TestNameNONE { TEXT("NONE"), FNAME_Add };
		bool const bTestNameNONE_IsNone = TestNameNONE.IsNone();

		static FName const TestNamenone { TEXT("none"), FNAME_Add };
		bool const bTestNamenone_IsNone = TestNamenone.IsNone();

		UE_LOG(MyLibLog, Log, TEXT(" bEmpty_IsNone: %s"), *YesNo(bEmpty_IsNone));
		UE_LOG(MyLibLog, Log, TEXT(" bTestNameNone_IsNone: %s"), *YesNo(bTestNameNone_IsNone));
		UE_LOG(MyLibLog, Log, TEXT(" bTestNameNONE_IsNone: %s"), *YesNo(bTestNameNONE_IsNone));
		UE_LOG(MyLibLog, Log, TEXT(" bTestNamenone_IsNone: %s"), *YesNo(bTestNamenone_IsNone));
	}

	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoLengthEmpty DONE"));
}

FString UMyStrBlueprintLib::YesNo(bool bYes)
{
	return bYes ? FString("YES") : FString("no");
}

void UMyStrBlueprintLib::TransformToString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::TransformToString"));

	static FName const TestName { TEXT("Test"), FNAME_Add };
	static FString TestString = TestName.ToString();

	// Comparing of name with TestString:
	check(TestName.ToString() == TestString);
	check(TestString == TestName.ToString());

	// Text also can be converted to FString with ToString()
}

void UMyStrBlueprintLib::ConvertToCString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::ConvertToCString"));

	FName MyFName { TEXT("TestName"), FNAME_Add };
	UE_LOG(MyLibLog, Log, TEXT("*MyFName: %s"), *MyFName.ToString());

	FString Str { TEXT("Str") };
	UE_LOG(MyLibLog, Log, TEXT("*Str: %s"), *Str);

	FText TextStr = FText::FromString( TEXT("TextStr") );
	UE_LOG(MyLibLog, Log, TEXT("*TextStr->ToString(): %s"), *TextStr.ToString())
}

void UMyStrBlueprintLib::DoConstruct_CString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct"));

	DoConstruct_FStringFrom_CString();
}

void UMyStrBlueprintLib::DoConstruct_FText()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_FText"));
	DoConstruct_FTextFrom_CString();
	DoConstruct_FTextFrom_Literal();
}

void UMyStrBlueprintLib::DoConstruct_FName()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_FName"));
	DoConstruct_NameFrom_CString();
}

void UMyStrBlueprintLib::DoConstruct_NameFrom_CString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_NameFrom_CString"));

	// Initialize FName
	static FName DefaultPlayerName { TEXT("DefaultPlayer"), FNAME_Add };
	static FName DefaultPlayerName2 { TEXT("DefaultPlayer"), FNAME_Add };
	static FName DefaultPlayerName3 = TEXT("DefaultPlayer");
	static FName DefaultPlayerName4 = "DefaultPlayer";
	check(DefaultPlayerName == DefaultPlayerName2); //?

	static const TCHAR* PlayerNameToSearchString = TEXT("DefaultPlayer");

	static FName PlayerNameToSearch { PlayerNameToSearchString, FNAME_Find };
	// WARNING!!! Know that there's NO "F" in front of NAME_None!
	check(PlayerNameToSearch != NAME_None);
	check(PlayerNameToSearch == DefaultPlayerName); // Comparison by index

	static FName InexistentPlayerNameToSearch { TEXT("WrongTypedPlayerName"), FNAME_Find };
	// WARNING!!! We do NOT check that the name does NOT exist - it may exist!
}


void UMyStrBlueprintLib::DoConstruct_FStringFrom_CString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_FStringFrom_CString"));
	FString S { TEXT("S") };
	FString S2 { "S2" }; // OK
}

void UMyStrBlueprintLib::DoConstruct_FTextFrom_CString()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_FTextFrom_CString"));
	FText S = FText::FromString(TEXT("S"));
	FText S2 = FText::FromString("S2");
}

void UMyStrBlueprintLib::DoConstruct_FTextFrom_Literal()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoConstruct_FTextFrom_Literal"));
	FText const PlayerName = LOCTEXT("PlayerName", "Player");

	UE_LOG(MyLibLog, Log, TEXT("PlayerName: %s"), *PlayerName.ToString());
}

void UMyStrBlueprintLib::DoCopy()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoCopy"));
}

void UMyStrBlueprintLib::DoLog()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoLog"));
}

void UMyStrBlueprintLib::DoFormat()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoFormat"));

	{
		// Both FString and C-String works
		TArray<FStringFormatArg> MyMsgArgs;
		MyMsgArgs.Add(FStringFormatArg(TEXT("Vasya")));
		MyMsgArgs.Add(FStringFormatArg(FString(TEXT("GetStatus"))));
		MyMsgArgs.Add(FStringFormatArg(15.1F));

		// {0}, {1}, {2} - Args
		FString MyMsg = FString::Format(TEXT("Hello, {0}: cmd={1}; temperature={2}"), MyMsgArgs);

		// Arguments as TMap
		TMap<FString,FStringFormatArg> MyMsgArgsMap;
		MyMsgArgsMap.Add(FString(TEXT("Name")), FStringFormatArg(TEXT("Vasya")));
		MyMsgArgsMap.Add(FString(TEXT("Status")),FStringFormatArg(FString(TEXT("GetStatus"))));
		MyMsgArgsMap.Add(FString(TEXT("Temp")), FStringFormatArg(15.1F));

		FString MyMsgByMap = FString::Format(TEXT("Hello, {Name}: cmd={Status}; temperature={Temp}"), MyMsgArgsMap);
	}

	{
		// Formatting FText:
		const FText Value = FText::FromString("Val");

		const FText Key = FText::FromString(TEXT("TheKey"));
		const FText FormatResult = FText::Format(FText::FromString("Key=\"{0}\" Value=\"{1}\""), Key, Value);

		//const FString StringKey = TEXT("TheKey");
		//const FText FormatResult = FText::Format(FText::FromString("Key=\"{0}\" Value=\"{1}\""), StringKey, Value);

		//M_LOG(TEXT("FText::Format result: %s"), *FormatResult.ToString());
	}
}

void UMyStrBlueprintLib::DoPrintf()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoPrintf"));
	FString S = FString::Printf(TEXT("C=%d; S=\"%s\""), 3, TEXT("MyStr"));
	UE_LOG(MyLibLog, Log, TEXT("S: %s"), *S);
}

void UMyStrBlueprintLib::DoIterator()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoIterator"));
	FString const S = "TestString";
	TCHAR const CharToFind = 'e';
	int32 Index = 0;
	for(auto Itr = S.CreateConstIterator(); Itr; ++Itr)
	{
		if(*Itr == CharToFind)
		{
			UE_LOG(MyLibLog, Log, TEXT("Char Found at Index: %d"), Index);
			break;
		}
		Index++;
	}
}

void UMyStrBlueprintLib::DoIndex()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoIndex"));
}

void UMyStrBlueprintLib::DoPattern()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoPattern"));
}

void UMyStrBlueprintLib::DoPath()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoPath"));

	FString const MyLogFilenameName { TEXT("MyLog.txt") };	

	FString const ProjDir = FPaths::ProjectLogDir();
	UE_LOG(MyLibLog, Log, TEXT("Log dir: %s"), *ProjDir);

	FString const MyLogPath = FPaths::Combine(ProjDir, MyLogFilenameName);
	UE_LOG(MyLibLog, Log, TEXT("MyLogPath: %s"), *MyLogPath);
}

void UMyStrBlueprintLib::DoResizeReserve()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoResizeReserve"));
}

void UMyStrBlueprintLib::DoReplace()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoReplace"));
}

void UMyStrBlueprintLib::DoRemove()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoRemove"));
}

void UMyStrBlueprintLib::DoAppend()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoAppend"));

	FString S { TEXT("PREF_") };
	FText T = FText::FromString( TEXT("PREF_") );

	{
		// Appending to string 
		S.Append(FString(TEXT("Count=")));
		S.AppendInt(32);
	}

	{
		// Appending to text 
		// WARNING: Append: "Undeclared identifier" for FText!!!
		T = FText::Format(FText::FromString("{0} {1}"), T, FText::FromString(TEXT("Count=")));
	}

	UE_LOG(MyLibLog, Log, TEXT("S=\"%s\""), *S);
	UE_LOG(MyLibLog, Log, TEXT("T=\"%s\""), *T.ToString());
}

void UMyStrBlueprintLib::DoInsert()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoInsert"));
}

void UMyStrBlueprintLib::DoFind()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoFind"));

	FString const PathToDoc { TEXT("C:\\UE4\\doc.txt") };
	UE_LOG(MyLibLog, Log, TEXT("PathToDoc: %s"), *PathToDoc);

	int32 LastPathSepIndex = 0;
	bool const bContainsPathSep = PathToDoc.FindLastChar(TCHAR('\\'), /*out*/LastPathSepIndex);
	UE_LOG(MyLibLog, Log, TEXT("bContainsPathSep: %s"), (bContainsPathSep ? TEXT("YES") : TEXT("no")));
	if(bContainsPathSep)
	{
		UE_LOG(MyLibLog, Log, TEXT("Last path sep index: %d"), LastPathSepIndex);

		bool bContainsExt = PathToDoc.Find(TEXT("."), ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromEnd, /*out*/LastPathSepIndex) >= 0;
		UE_LOG(MyLibLog, Log, TEXT("bContainsExt: %s"), (bContainsExt ? TEXT("YES") : TEXT("no")));
		if(bContainsExt)
		{
			UE_LOG(MyLibLog, Log, TEXT("LastPathSepIndex: %d"), LastPathSepIndex);
		}
	}

	bool const bContainsPoint = PathToDoc.Contains(TEXT("."), ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromEnd);
	UE_LOG(MyLibLog, Log, TEXT("bContainsPoint: %s"), (bContainsPoint ? TEXT("YES") : TEXT("no")));
}

void UMyStrBlueprintLib::DoSubstring()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoSubstring"));
}

void UMyStrBlueprintLib::DoLeftRightMid()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoLeftRightMid"));

	TCHAR const SEP_CHAR = TCHAR(':');
	FString KeyValueStr = " filename  :   myfile.txt.rar ";	

	int32 SepIndex = -1;
	bool bSepFound = KeyValueStr.FindChar(SEP_CHAR, /*Out*/SepIndex);
	
	check(bSepFound);
	FString const Key = KeyValueStr.Left(SepIndex).TrimStartAndEnd();
	FString FilenameValue = KeyValueStr.Right(SepIndex).TrimStartAndEnd();

	bool bArchive = FilenameValue.RemoveFromEnd(".rar", ESearchCase::Type::IgnoreCase);
	check(bArchive);
	 
}

void UMyStrBlueprintLib::DoCase()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoCase"));
}

void UMyStrBlueprintLib::DoParse()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoParse"));

	DoParse_Int();
	DoParse_Int_Atoi();
	DoParse_Float();
	DoParse_Float_Atof();
}

void UMyStrBlueprintLib::DoParse_Int()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoParse_Int..."));

	// FDefaultValueHelper::ParseInt:
	// 1. Trims whitesspaces
	// 2. 1.5. 3.5 will NOT be parsed
	// 3. -7, -3 - parsed correctly

	// FParse::Value
	// 1) When we pass nullptr as second argument (pMatch) of the FParse::Value,
	// always returned false and parses to zero!
	// 2) When we pass as FParse(*S, *S, val) it does not work also!!!
	
	const TCHAR* const SEP = TEXT(";");
	FString const SourceSequenceStr = " 1  ; test   ; 3;;; test_str2; 3; -7; -12.3; 1.5; -1.5; 0; 0003";

	TArray<FString> Sequence;
	int32 CountElems = SourceSequenceStr.ParseIntoArray(/*Out*/Sequence, SEP, /*bCullEmpty*/true);
	check(CountElems > 0);

	TArray<int32> NumberSequence;
	TArray<int32> NumberSequence_FromNonTrimmed;

	for(const FString& S : Sequence)
	{
		FString TrimmedS = S.TrimStartAndEnd();

		// WARNING!!! The main line
		UE_LOG(MyLibLog, Log, TEXT("FDefaultValueHelper::ParseInt(TrimmedS, val)..."));
		int32 ParsedValue_FromTrimmedParse = 0;
		//bool bTrimmedParse = FParse::Value(*TrimmedS, /*Match*/*TrimmedS, /*Out*/ParsedValue_FromTrimmedParse);
		bool bTrimmedParse = FDefaultValueHelper::ParseInt(TrimmedS, ParsedValue_FromTrimmedParse);
		UE_LOG
		(
			MyLibLog, Log, TEXT("bTrimmedParse: %s; ParsedValue: %d"), 
			(bTrimmedParse ? TEXT("YES") : TEXT("NO")), 
			ParsedValue_FromTrimmedParse
		);
		if(bTrimmedParse)
		{
			NumberSequence.Add(ParsedValue_FromTrimmedParse);
		}
	}

	for(const FString& S : Sequence)
	{
		// WARNING!!! The main line
		UE_LOG(MyLibLog, Log, TEXT("FDefaultValueHelper::ParseInt(S, val)..."));
		int32 ParsedValue = 0;
		//bool bParse = FParse::Value(*S, /*Match*/nullptr, /*Out*/ParsedValue);
		bool bParse = FDefaultValueHelper::ParseInt(S, ParsedValue);
		UE_LOG
		(
			MyLibLog, Log, TEXT("bParse: %s; ParsedValue: %d"), 
			(bParse ? TEXT("YES") : TEXT("NO")), 
			ParsedValue
		);
		if(bParse)
		{
			NumberSequence_FromNonTrimmed.Add(ParsedValue);
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers"));
	{
		int32 NumIndex = 0;
		for(int32 N : NumberSequence)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%d"), NumIndex, N);
			NumIndex++;
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers from Non-trimmed"));
	{
		int32 NumIndex = 0;
		for(int32 N : NumberSequence_FromNonTrimmed)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%d"), NumIndex, N);
			NumIndex++;
		}
	}
}

void UMyStrBlueprintLib::DoParse_Int_Atoi()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoParse_Int_Atoi..."));

	//
	// FString::IsNumeric parses: 0003, -123: correctly
	//
	// FCString::Atoi returns 0 if parsed incorrectly;
	//
	// FCString::Atoi parses 0003 correctly;
	//
	//

	const TCHAR* const SEP = TEXT(";");
	FString const SourceSequenceStr { " 1  ; test   ; 3;;; test_str2; 3; -7; -12.3; 1.5; -1.5; 0; 0003" };
	
	TArray<FString> Sequence;
	int32 CountElems = SourceSequenceStr.ParseIntoArray(/*Out*/Sequence, SEP, /*bCullEmpty*/true);
	check(CountElems > 0);
	
	TArray<int32> NumberSequence;
	TArray<FString> StrSequence;
	for(const FString& S : Sequence)
	{
		if(S.TrimStartAndEnd().IsNumeric())
		{
			NumberSequence.Add(FCString::Atoi(*S.TrimStartAndEnd()));
		}
		else
		{
			StrSequence.Add(S.TrimStartAndEnd());
		}
	}

	TArray<int32> NumberSequence_NonTrimmed;
	for(const FString& S : Sequence)
	{
		if(S.IsNumeric())
		{
			NumberSequence_NonTrimmed.Add(FCString::Atoi(*S));
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers"));
	{
		int32 NumIndex = 0;
		for(int32 N : NumberSequence)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%d"), NumIndex, N);
			NumIndex++;
		}
	}


	UE_LOG(MyLibLog, Log, TEXT("Numbers_NonTrimmed"));
	{
		int32 NumIndex = 0;
		for(int32 N : NumberSequence_NonTrimmed)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%d"), NumIndex, N);
			NumIndex++;
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Strings"));
	int32 NameIndex = 0;
	for(const FString& NameStr : StrSequence)
	{
		UE_LOG(MyLibLog, Log, TEXT("index=%d, String=\"%s\""), NameIndex, *NameStr);
		NameIndex++;
	}
}

void UMyStrBlueprintLib::DoParse_Float()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoParse_Float..."));

	// FDefaultValueHelper::ParseFloat:
	// 1. Trims whitesspaces
	
	const TCHAR* const SEP = TEXT(";");
	FString const SourceSequenceStr = " 1  ; test   ; 3;;; test_str2; 3; -7; -12.3; 1.5; -1.5; 0; 0003";

	TArray<FString> Sequence;
	int32 CountElems = SourceSequenceStr.ParseIntoArray(/*Out*/Sequence, SEP, /*bCullEmpty*/true);
	check(CountElems > 0);

	TArray<float> NumberSequence;
	TArray<float> NumberSequence_FromNonTrimmed;

	for(const FString& S : Sequence)
	{
		FString TrimmedS = S.TrimStartAndEnd();

		// WARNING!!! The main line
		UE_LOG(MyLibLog, Log, TEXT("FDefaultValueHelper::ParseFloat(TrimmedS, val)..."));
		float ParsedValue_FromTrimmedParse = 0;
		bool bTrimmedParse = FDefaultValueHelper::ParseFloat(TrimmedS, ParsedValue_FromTrimmedParse);
		UE_LOG
		(
			MyLibLog, Log, TEXT("bTrimmedParse: %s; ParsedValue: %f"), 
			(bTrimmedParse ? TEXT("YES") : TEXT("NO")), 
			ParsedValue_FromTrimmedParse
		);
		if(bTrimmedParse)
		{
			NumberSequence.Add(ParsedValue_FromTrimmedParse);
		}
	}

	for(const FString& S : Sequence)
	{
		// WARNING!!! The main line
		UE_LOG(MyLibLog, Log, TEXT("FDefaultValueHelper::ParseFloat(S, val)..."));
		float ParsedValue = 0;
		bool bParse = FDefaultValueHelper::ParseFloat(S, ParsedValue);
		UE_LOG
		(
			MyLibLog, Log, TEXT("bParse: %s; ParsedValue: %f"), 
			(bParse ? TEXT("YES") : TEXT("NO")), 
			ParsedValue
		);
		if(bParse)
		{
			NumberSequence_FromNonTrimmed.Add(ParsedValue);
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers"));
	{
		int32 NumIndex = 0;
		for(float N : NumberSequence)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%f"), NumIndex, N);
			NumIndex++;
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers from Non-trimmed"));
	{
		int32 NumIndex = 0;
		for(float N : NumberSequence_FromNonTrimmed)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%f"), NumIndex, N);
			NumIndex++;
		}
	}
	
}

void UMyStrBlueprintLib::DoParse_Float_Atof()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoParse_Float_Atof..."));

const TCHAR* const SEP = TEXT(";");
	FString const SourceSequenceStr { " 1  ; test   ; 3;;; test_str2; 3; -7; -12.3; 1.5; -1.5; 0; 0003" };
	
	TArray<FString> Sequence;
	int32 CountElems = SourceSequenceStr.ParseIntoArray(/*Out*/Sequence, SEP, /*bCullEmpty*/true);
	check(CountElems > 0);
	
	TArray<float> NumberSequence;
	TArray<FString> StrSequence;
	for(const FString& S : Sequence)
	{
		if(S.TrimStartAndEnd().IsNumeric())
		{
			NumberSequence.Add(FCString::Atof(*S.TrimStartAndEnd()));
		}
		else
		{
			StrSequence.Add(S.TrimStartAndEnd());
		}
	}

	TArray<int32> NumberSequence_NonTrimmed;
	for(const FString& S : Sequence)
	{
		if(S.IsNumeric())
		{
			NumberSequence_NonTrimmed.Add(FCString::Atof(*S));
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Numbers"));
	{
		int32 NumIndex = 0;
		for(float N : NumberSequence)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%f"), NumIndex, N);
			NumIndex++;
		}
	}


	UE_LOG(MyLibLog, Log, TEXT("Numbers_NonTrimmed"));
	{
		int32 NumIndex = 0;
		for(float N : NumberSequence_NonTrimmed)
		{
			UE_LOG(MyLibLog, Log, TEXT("index=%d, num=%f"), NumIndex, N);
			NumIndex++;
		}
	}

	UE_LOG(MyLibLog, Log, TEXT("Strings"));
	int32 NameIndex = 0;
	for(const FString& NameStr : StrSequence)
	{
		UE_LOG(MyLibLog, Log, TEXT("index=%d, String=\"%s\""), NameIndex, *NameStr);
		NameIndex++;
	}
}

void UMyStrBlueprintLib::DoSerialize()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoSerialize"));

	int32 TestInt_REF = 1;
	int32 const ConstTestInt_REF = 2;

	FName CurrentGoalIdentifier_REF { "CurrentGoal" };
	FString AccessCode_REF { "MyPlayer" };
	FText PlayerName_REF = LOCTEXT( "SerializePlayerNameRef", "MyPlayer" );

	FName const ConstCurrentGoalIdentifier_REF { "CurrentGoal" };
	FString const ConstAccessCode_REF { "MyPlayer" };
	FText const ConstPlayerName_REF = LOCTEXT( "SerializePlayerNameRef", "MyPlayer" );

	{
		FBufferArchive Buffer;

		UE_LOG(MyLibLog, Log, TEXT("Serializing strings..."));
		{
			// Serializing just Int: works
			{
				Buffer << TestInt_REF;
			}

			// Serializing ConstInt:
			{
				// error C2679: operator<<: not found taking right "const int32"
				//Buffer << ConstTestInt_REF;
			}


			// Serializing FName
			{
				Buffer << CurrentGoalIdentifier_REF;
				// Serializing "const FName": does NOT work
			}

			// Serializing String:
			{
				Buffer << AccessCode_REF;
				// Serializing "const FString": does NOT work
			}

			// Serializing Text:
			{
				Buffer << PlayerName_REF;
				// Serializing "const FText": does NOT work
			}
		}

		UE_LOG(MyLibLog, Log, TEXT("Deserializing strings..."));
		{
			FName CurrentGoalIdentifier;
			FString AccessCode;
			FText PlayerName;

			// WARNING!!! When deserializing, operator<< also means "Extract"!!!
			FMemoryReader MemoryReader { Buffer, /*bPersistent=*/true }; // bPersistent=true
			MemoryReader << CurrentGoalIdentifier;
			MemoryReader << AccessCode;
			MemoryReader << PlayerName;

			UE_LOG(MyLibLog, Log, TEXT("CurrentGoalIdentifier: %s"), *CurrentGoalIdentifier.ToString());
			UE_LOG(MyLibLog, Log, TEXT("AccessCode: %s"), *AccessCode);
			UE_LOG(MyLibLog, Log, TEXT("PlayerName: %s"), *PlayerName.ToString());

			UE_LOG(MyLibLog, Log, TEXT("Checking that deserialized data correspond to what was serialized..."));
			{
				check(CurrentGoalIdentifier.ToString().Equals(CurrentGoalIdentifier_REF.ToString()));
				check(AccessCode.Equals(AccessCode_REF));			
				check(PlayerName.EqualTo(PlayerName_REF));
			}
		}
	}
}

void UMyStrBlueprintLib::DoMiscRange()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoMiscRange"));

	TArray<FString> MyText;
	MyText.Add(FString(TEXT("One")));
	MyText.Add(FString(TEXT("")));
	MyText.Add(FString(TEXT("Two")));
	MyText.Add(FString(TEXT("")));
	MyText.Add(FString(TEXT("")));
	MyText.Add(FString(TEXT("Three")));

	// Culling empty strings
	FString::CullArray(&MyText);
	
	int32 index = 0;
	for(const FString& S : MyText)
	{
		UE_LOG(MyLibLog, Log, TEXT("%d: %s"), index, *S);
		index++;
	}
}

namespace
{
	void DoTest_HexBlob()
	{
		UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoTest_HexBlob"));	

		TArray<uint8> MyBlob = MyCreateRandomByteArray(10);
		FString MyBlobString = FString::FromHexBlob(MyBlob.GetData(), MyBlob.Num());
	
		UE_LOG(MyLibLog, Log, TEXT("Data: %s"), *MyBlobString);
	}
} // anonymous-namespace

void UMyStrBlueprintLib::DoMisc()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoMisc"));	
	DoTest_HexBlob();
}

void UMyStrBlueprintLib::DoTest()
{
	UE_LOG(MyLibLog, Log, TEXT("UMyStrBlueprintLib::DoTest"));
}

#undef LOCTEXT_NAMESPACE
