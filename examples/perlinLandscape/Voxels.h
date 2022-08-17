#pragma once
#include "IVoxel.h"

class GrassVoxel : public IVoxel
{
public:
	virtual ~GrassVoxel() = default;
	color getColor() const override { return color(0.0f, 0.95f, 0.0f); }
	bool getIsActive() const override { return active; }
	void setActive(bool isActive) override { active = isActive; };

private:
	bool active = true;
};

class MountainVoxel : public IVoxel
{
public:
	virtual ~MountainVoxel() = default;
	color getColor() const override { return color(0.5f, 0.5f, 0.5f); }
	bool getIsActive() const override { return active; }
	void setActive(bool isActive) override { active = isActive; };

private:
	bool active = true;
};

class SnowVoxel : public IVoxel
{
public:
	virtual ~SnowVoxel() = default;
	color getColor() const override { return color(0.95f, 0.95f, 0.95f); }
	bool getIsActive() const override { return active; }
	void setActive(bool isActive) override { active = isActive; };

private:
	bool active = true;
};

class WoodVoxel : public IVoxel
{
public:
	virtual ~WoodVoxel() = default;
	color getColor() const override { return color(0.71f, 0.38f, 0.078f); } // 181, 98, 20
	bool getIsActive() const override { return active; }
	void setActive(bool isActive) override { active = isActive; };

private:
	bool active = true;
};