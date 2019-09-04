#ifndef LYSimDetectorConstruction_h
#define LYSimDetectorConstruction_h 1

#include "LYSimPMTSD.hh"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class LYSimDetectorMessenger;
class G4Box;
class G4LogicalVolume;
class G4Material;
class G4OpticalSurface;
class LYSimPMTSD;

class LYSimDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  LYSimDetectorConstruction();
  virtual ~LYSimDetectorConstruction();
  virtual G4VPhysicalVolume* Construct();
  void                       UpdateGeometry();


  // Toggle Tyvek on or off
  inline void
  SetWrappingToggle ( const G4bool x ){wrapping_toggle = x;}
  inline G4bool
  GetWrappingToggle () const {return wrapping_toggle;}

  // Set ref index of scint pmt gap
  inline void
  SetRefIndex ( const G4double iRefIndex ){RefIndex = iRefIndex;}
  inline G4double
  GetRefIndex() const {return RefIndex;}

  inline void
  SetScintThickness ( const G4double x ){ scint_thickness = x;}
  inline G4double
  GetScintThickness() const {return scint_thickness;}

  inline void
  SetScintSizeX ( const G4double x ){scint_sizeX = x;}
  inline G4double
  GetScintSizeX() const {return scint_sizeX;}

  inline void
  SetScintSizeY ( const G4double y ){scint_sizeY = y;}
  inline G4double
  GetScintSizeY() const {return scint_sizeY;}

  inline void
  SetScintPMTGapThickness ( const G4double x ){ScintPMT_gap = x;}
  inline G4double
  GetScintPMTGapThickness() const {return ScintPMT_gap;}

  inline void
  SetTileAbsLength ( const G4double x ){tileAbsLength = x;}
  inline G4double
  GetTileAbsLength() const {return tileAbsLength;}

  inline void
  SetInducedMuTile( const G4double x ){inducedMuTile = x;}
  inline G4double
  GetInducedMuTile() const {return inducedMuTile;}

  inline G4double
  GetMinZ() const {return minZposition;}
  inline G4double
  GetMaxZ() const {return maxZposition;}

  inline double
  GetDimpleRadius() const { return Rad; }
  inline double
         GetDimpleIndent() const { return Din; }
  double GetDimpleSizeRadius() const;

  int GetDimpleType() const {return DimpleType; }
  inline double GetTileThickness() const { return scint_thickness; }

private:
  // Subfunctions for cleaner code
  void               DefineSurfaces();
  void               SetDefaults();// *-*Doesn't seem to work right now
  G4VPhysicalVolume* ConstructDetector();
  G4VSolid*          ConstructTileSolid(
    const G4String& name,
    G4double        angle1, // angle measured ccw from y axis for the side at -x
    G4double        angle2, // angle measured ccw from y axis for the side at +x
    G4double        Dx2,    // length along x of side at y=+Dy
    G4double        Dy,     // length along y
    G4double        Dz,     // length along z
    G4ThreeVector&  centerCoord ); // coordinate of center of gravity w.r.t.
                                   // corner 0 at -x, -y

  // Pointer to detector messenger class
  LYSimDetectorMessenger* fdetectorMessenger;

  G4bool fUpdated;

  // Contains the minimum and maximum Z-position of the previously defined volume
  // Use this variable to define volume successively along the z-axis
  // (max for +z direction, min for -z direction)
  // Set value after defining a physical volume
  G4double minZposition;
  G4double maxZposition;

  // Pointers to main volumes
  G4Box* solidWorld;
  G4LogicalVolume* logicWorld;
  G4VPhysicalVolume* physWorld;
  G4VPhysicalVolume* physRod;

  // pointer for wrapping
  G4LogicalVolume* logicWWW;
  // pointer for dimple
  G4LogicalVolume* logicD;

  // Pointers to materials
  G4Material* fAir;
  G4Material* fSCSN81;
  G4Material* fEJ200;
  G4Material* fEJ260;
  G4Material* fBialkali;
  G4Material* fEpoxy;
  G4Material* fEpoxy2;

  // Pointers to surfaces
  G4OpticalSurface* fTyvekOpSurface;
  G4OpticalSurface* fIdealTyvekOpSurface;
  G4OpticalSurface* fUnifiedTyvekOpSurface;
  G4OpticalSurface* fUnifiedIdealTyvekOpSurface;
  G4OpticalSurface* fESROpSurface;
  G4OpticalSurface* fPolishedOpSurface;
  G4OpticalSurface* fIdealPolishedOpSurface;
  G4OpticalSurface* fMirrorOpSurface;
  G4OpticalSurface* fIdealMirrorOpSurface;
  G4OpticalSurface* fAbsorbingOpSurface;
  G4OpticalSurface* fRoughOpSurface;


  // Pointers for access to Sensitive Detector
  static LYSimPMTSD* fPMTSD;

  // Geometry parameters
  // Important parameters marked with ////
  G4bool wrapping_toggle;// (Tyvek) wrapping around scintillator
  G4double RefIndex;// Refractive index of fiber or scint-PMT gap
  G4double angle1;
  G4double angle2;
  G4double angle3;
  G4double Dx2;
  G4double Dx3;
  G4double Dw2;
  G4double world_sizeX;
  G4double world_sizeY;
  G4double world_sizeZ;
  G4double scint_sizeX;
  G4double scint_sizeY;
  G4double scint_thickness;
  G4double Photocat_sizeX;
  G4double Photocat_sizeY;
  G4double Photocat_thickness;
  G4double ScintPMT_gap;// thickness of gap between scintillator and PMT
  G4double wrapgap;// distance between tile and wrapping
  G4double tileAbsLength;
  G4double inducedMuTile;// Radiation-induced absorption coefficient (cm^-1)
  G4double Absmultiple;// factor for Abslength manipulation.
  G4double Din;// Depth of dimple
  G4double deft;// default radius
  G4double Rad;// Dimple radius
  G4double SiPM_Depth;// SiPM depth
  G4double aSiPM;

  G4ThreeVector corners[8];// stores the corner coordinates of the tile
  G4ThreeVector readout0, readout1;// location of readout at corner 0/1
  // G4ThreeVector mirror0, mirror1;     //location of mirrors at corner 0/1
  G4int readoutCorner;// determines location of fiber readout (0:corner 0, 1:corner 1)
  G4int DimpleType;
};

#endif