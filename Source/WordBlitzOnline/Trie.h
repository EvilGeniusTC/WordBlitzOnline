// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Templates/SharedPointer.h"
#include "Trie.generated.h"

USTRUCT(BlueprintType)
struct FTrieNode
{
	GENERATED_BODY()

		TMap<TCHAR, TSharedPtr<FTrieNode>> Children;
	bool bEndOfWord;
};

UCLASS(Blueprintable)
class ATrie : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<USceneComponent> DefaultRoot;

	TSharedPtr<FTrieNode> TrieRootPtr = MakeShareable(new FTrieNode);
	TSharedRef<FTrieNode> TrieRootRef = TrieRootPtr.ToSharedRef();

	UFUNCTION(BlueprintCallable)
		void InsertTrieNode(const TArray<FString> Dictionary);
	UFUNCTION(BlueprintCallable)
		bool SearchTrie(const FString Word);
};
