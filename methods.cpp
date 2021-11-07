#include "classes.h"
#include <cmath>
using namespace std; 

<template T>
T interpolate(T x0, T y0, T x1, T y1, T x) {
    T linearInterpolation = (y1 - y0) / (x1 - x0) * (x - x0) + y0;
    return linearInterpolation;
}

float Engine::interpolateTorque() {
    int lowPoint = RPM % 100 * 100;
    int highPoint = lowPoint + 100;
    return interpolate<float> (lowPoint, torqueMap[(startRPM + lowPoint) / 10], highPoint, torqueMap[(startRPM + highPoint) / 10]);
}

float Engine::calculateCurrentPower() {
    return interpolateTorque() * RPM;
}

float Position::calculatePosition(float speed, float timeDelta=0.01) {
    return range + speed * timeDelta;
}

void Position::setRange(float range) {
    this->range = range;
}

float Car::calculateCurrentVelocity(float timeDelta) {
    float enginePower = engine->calculateCurrentPower();
    float dragPower = velocity * atmosphere->calculateDrag(velocity, surfaceArea);
    float effectivePower = enginePower - dragPower;
    if (effectivePower < 0) {
        return velocity;
    } else {
        velocity = sqrt(2*effectivePower * timeDelta / mass + pow(velocity, 2));
        return velocity;
    }
}

void Car::setVelocity(float velocity) {
    this->velocity = velocity;
}

float Atmosphere::calculateDrag(float velocity, float surfaceArea) {
    return (airDensity * pow(velocity, 3)) / 2 * surfaceArea;
}

float GearBox::calculateRPM(float velocity, float diameter) {
    return velocity / diameter / M_PI;
}

Car::Car(string name, int mass, float velocity, float surfaceArea, Position *position, Engine *engine, GearBox *gearBox, TyreSet *tyreSet, Atmosphere *atmosphere) {
    this->name = name;
    this->mass = mass;
    this->velocity = velocity;
    this->surfaceArea = surfaceArea;
    this->position = position;
    this->engine = engine;
    this->gearBox = gearBox;
    this->tyreSet = tyreSet;
    this->atmosphere = atmosphere;
}

Atmosphere::Atmosphere(float airDensity) {
    this->airDensity = airDensity;
}

Position::Position(float range) {
    this->range = range;
}

Engine::Engine(int RPM, int minRPM, int maxRPM, vector<int> torqueMap) {
    this->RPM = RPM;
    this->minRPM = minRPM;
    this->maxRPM = maxRPM;
    this-> torqueMap = torqueMap;
}

TyreSet::TyreSet(float diameter) {
    this->diameter = diameter;
}

GearBox::GearBox(vector<int> ratioMap) {
    this->ratioMap = ratioMap;
}
