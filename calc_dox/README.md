Calc_dox written in C++ with Qt/QML

It calculates the thickness of gate insulator dox (![equation](http://latex.codecogs.com/gif.latex?d_%7Box%7D)) of NMOS structure with Poly-Si Gate with given
* phims(![equation](http://latex.codecogs.com/gif.latex?\phi) metal-semiconductor (eV)),
* phiF (Fermi level for n-type semiconductor (eV)),
* eox (![equation](http://latex.codecogs.com/gif.latex?%5Cvarepsilon%20_%7Box%7D) oxide permittivity),
* esub (![equation](http://latex.codecogs.com/gif.latex?%5Cvarepsilon%20_%7Bsub%7D) dielectric constant of the substrate),
* Nsub (![equation](http://latex.codecogs.com/gif.latex?N%20_%7Bsub%7D) substrate doping density(![equation](http://latex.codecogs.com/gif.latex?1/%28sm%5E%7B-3%7D%29)),
* Vsub (![equation](http://latex.codecogs.com/gif.latex?V_%7Bsub%7D) substrate bias voltage (V)),
* qox (![equation](http://latex.codecogs.com/gif.latex?q%20_%7Box%7D) oxide charge (given 0 C)),
* Vth (![equation](http://latex.codecogs.com/gif.latex?V_%7Bth%7D) threshhold voltage (given 0.7 V));

Also renders 2 plots:
1. Graph of the threshhold voltage from substrate doping density; (points for graph are transferred to QML as QVariantList);
2. Graph of the threshhold voltage from substrate bias voltage; (points for graph are transferred to QML as QAbstractListModel derived model)

If you have questions or ideas for improvement this project, don't hesitate and mail me (alex.and.riaqqq@gmail.com).
