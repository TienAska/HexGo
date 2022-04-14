// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HexBlueprintLibrary.generated.h"

struct FHex
{
public:
	FHex(float x, float y, float size) :
		q((FGenericPlatformMath::Sqrt(3) / 3 * y - 1.0 / 3 * x) / size), r((2.0 / 3 * x) / size), size(size)
	{
	}

	FHex& Round()
	{
		float _q = round(q);
		float _r = round(r);
		float _s = round(-q - r);

		float q_diff = abs(_q - q);
		float r_diff = abs(_r - r);
		float s_diff = abs(_s - (-q - r));

		if (q_diff > r_diff && q_diff > s_diff)
			_q = -_r - _s;
		else if (r_diff > s_diff)
			_r = -_q - _s;
		else
			_s = -_q - _r;

		q = _q;
		r = _r;
		return *this;
	}

	FVector Position() const
	{
		float x = size * (3.0 / 2 * r);
		float y = size * (sqrt(3) * q + sqrt(3) / 2 * r);

		return FVector(x, y, 0);
	}

private:
	float q, r, size;
};


/**
 * 
 */
UCLASS()
class HEXGO_API UHexBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Hex")
	static FVector SnapeToGrid(const FVector& worldPos, float size)
	{
		FHex hex(worldPos.X, worldPos.Y, size);
		return hex.Round().Position();
	}
};

