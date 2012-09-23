//Authoring the first logic entity
//std header
#include <cbase.h>

//using a 'class blueprint'
/**************************************************************************************************
The colon will tell the compiler that it is "inheriting" from Valve's pre-existing CLogicalEntity class (which we can reach thanks to our #include of cbase.h earlier).
Inheritance means basing a class on an existing one instead of starting from scratch. CLogicalEntity is itself quite simple, 
but there is a huge amount of code in the classes it inherits from in turn, going right back to CBaseEntity — 
without being able to inherit all of that, anyone trying to create a new entity would probably go mad.
**************************************************************************************************/
class CMyLogicalEntity : public CLogicalEntity
{
public:
	DECLARE_CLASS( CMyLogicalEntity, CLogicalEntity );
	//Now declare a DATASEC, no params
	DECLARE_DATASEC();

	//Constructor
	CMyLogicalEntity ()
	{
		int m_nCounter = 0;
	}

	//Input Func
	void InputTick( inputdata_t &inputdata );

private:
 
	int	m_nThreshold;	// Count at which to fire our output
	int	m_nCounter;	// Internal counter ( ASI : CMLE() )
 
	COutputEvent m_OnThreshold;	// Output event when the counter reaches the threshold


};

LINK_ENTITY_TO_CLASS( my_logical_entity, CMyLogicalEntity );
//Links "my_logical_entity" to CMLE()

// Start of our data description for the class
BEGIN_DATADESC ( CMyLogicalEntity )
		
	// For save/load
	DEFINE_FIELD( m_nCounter, FIELD_INTEGER ),
 
	// As above, and also links our member variable to a Hammer keyvalue
	DEFINE_KEYFIELD( m_nThreshold, FIELD_INTEGER, "threshold" ),
 
	// Links our input name from Hammer to our input member function
	DEFINE_INPUTFUNC( FIELD_VOID, "Tick", InputTick ),
 
	// Links our output member variable to the output name used by Hammer
	DEFINE_OUTPUT( m_OnThreshold, "OnThreshold" ),
 
	END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Handle a tick input from another entity
//-----------------------------------------------------------------------------
void CMyLogicalEntity::InputTick( inputdata_t &inputData )
{
	// Increment our counter
	m_nCounter++;
 
	// See if we've met or crossed our threshold value
	if ( m_nCounter >= m_nThreshold )
	{
		// Fire an output event
		m_OnThreshold.FireOutput( inputData.pActivator, this );
 
		// Reset our counter
		m_nCounter = 0;
	}
}