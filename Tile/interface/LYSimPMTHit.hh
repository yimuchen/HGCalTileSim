#ifndef LYSimPMTHit_h
#define LYSimPMTHit_h

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4VHit.hh"

class G4VTouchable;

// --------------------------------------------------
// LYSimPMTHit Class
// --------------------------------------------------

class LYSimPMTHit : public G4VHit
{
public:

  LYSimPMTHit();
  ~LYSimPMTHit();
  LYSimPMTHit( const LYSimPMTHit & right );

  const LYSimPMTHit& operator=( const LYSimPMTHit& right );
  G4int              operator==( const LYSimPMTHit& right ) const;

  inline void* operator new( size_t );
  inline void  operator delete( void* aHit );

  void Draw();
  void Print();

  void
  SetEnergy( G4double energy ){fEnergy = energy;}
  void
  SetPhotonCount( G4int photonCount ){fPhotonCount = photonCount;}
  void
  AddEnergy( G4double energy ){fEnergy += energy;}
  void
  IncPhotonCount(){fPhotonCount++;}

  G4double
  GetEnergy(){ return fEnergy; }
  G4int
  GetPhotonCount(){ return fPhotonCount;}

  void
  SetTime( G4double t ){fTime = t;};
  G4double
  GetTime(){return fTime;};

private:
  G4double fEnergy;   // Total photon energy deposited in PMT
  G4int fPhotonCount;   // Total number of photons detected by PMT
  G4double fTime;

};

// --------------------------------------------------
// Type Definitions
// --------------------------------------------------
typedef G4THitsCollection<LYSimPMTHit> LYSimPMTHitsCollection;
extern G4Allocator<LYSimPMTHit> LYSimPMTHitAllocator;

// --------------------------------------------------
// Operator Overloads
// --------------------------------------------------

inline void*
LYSimPMTHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)LYSimPMTHitAllocator.MallocSingle();
  return aHit;
}

inline void
LYSimPMTHit::operator delete( void* aHit )
{
  LYSimPMTHitAllocator.FreeSingle( (LYSimPMTHit*)aHit );
}

#endif
