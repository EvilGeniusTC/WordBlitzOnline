/// Fill out your copyright notice in the Description page of Project Settings.


#include "Trie.h"


// Sets default values
ATrie::ATrie()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATrie::BeginPlay()
{
	Super::BeginPlay();

}

void ATrie::InsertTrieNode(const TArray<FString> Dictionary)
{
	for (FString Word : Dictionary)
	{
		TSharedRef<FTrieNode> tmp = TrieRootRef;

		for (int32 i = 0; i < Word.Len(); ++i)
		{
			// Check if letter is found.
			if (!tmp->Children.Contains(Word[i]))
			{
				// Create a shared pointer to a new object
				TSharedPtr<FTrieNode> NewNode(new FTrieNode());
				// Add new node.
				tmp->Children.Add(Word[i], NewNode);
				// Move down to check on next loop.
				tmp = NewNode.ToSharedRef();

				NewNode.Reset();
			}
			else
			{
				// Move down to check on next loop.
				tmp = tmp->Children.Find(Word[i])->ToSharedRef();
			}
		}
		tmp->bEndOfWord = true;
	}
}

bool ATrie::SearchTrie(const FString Word)
{
	TSharedRef<FTrieNode> tmp = TrieRootRef;
	for (int32 i = 0; i < Word.Len(); ++i)
	{
		// Check if letter is found.
		if (!tmp->Children.Contains(Word[i]))
		{
			FString l;
			l.AppendChar(Word[i]);
			UE_LOG(LogTemp, Warning, TEXT("Letter not found: %s, %i"), *l, i);
			return false;
		}
		// Move down to check on next loop.
		tmp = tmp->Children.Find(Word[i])->ToSharedRef();
	}
	// All nodes were found.
	UE_LOG(LogTemp, Warning, TEXT("All letters found."));

	return tmp->bEndOfWord;
}