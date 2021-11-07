# Vehicle Kinematic Simulator

C++

## Klasy

* Position
* Car
* Engine
* GearBox
* TyreSet
* Atmosphere
* TestRun



## Zależności



**Car** posiada

* **Engine**
* **Position**
* **GearBox**
* **TyreSet**
* **Atmosphere**



**Car** posiada:

* mass [kg]
* surfaceArea [m^2]
* currentSpeed [m/s]



**TyreSet** posiada:

* diameter



**GearBox** posiada:

* ratioMap [przełożenie(obroty)]



**Engine** posiada:

* torqueMap [moment_siły(obroty)]



**Atmosphere** posiada:

* airDensity [kg/m^3]



**TestRun** posiada:

* main



## Metody

### Position

* calculatePosition
  * `velocity`
  * `timeDelta`

### Engine

* calculateCurrentPower
  * `this->torqueMap`
  * `ths->currentRPM`



### Car

* calculateCurrentSpeed
  * `this->engine->currentRPM`
  * `ths->mass`
  * `this->currentSpeed`

### Atmosphere

* calculateDrag
  * `this->airDensity`
  * `speed`
  * `surfaceArea`

## Wzorki

### Silnik i moc

$$
\Delta E_k = E_{k1} - E_{k0} = \frac{1}{2}m(v_1^2-v_0^2)
\\
P = \frac {\Delta E_k}{t}
\\
v_1 = \sqrt{\frac{2 P_e \cdot t}{m} + v_0^2}
\\
v_1 = \sqrt{\frac{2 \cdot P_e(obr) \cdot \Delta t}{m} + v_0^2}
$$

### Opory powietrza

$$
P_w = F_w \cdot v
\\
F_w = \frac{\rho_{atm} \cdot v^2}{2 S}
\\
P_{effective} = P_e(obr) - \frac{\rho_{atm} \cdot v^3}{2 S} \ \ if >0 \ \ else \ \ 0
\\
v_1 = \sqrt{\frac{2 \cdot P_{effective}(obr,v) \cdot \Delta t}{m} + v_0^2}
$$

