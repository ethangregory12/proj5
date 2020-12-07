#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generator seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() ||
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime <<
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime <<
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean <<
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean <<
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean <<
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean <<
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
   if (currentTime <= timeToStopSim)
   {
//Determine Next Arrival Time (Create an event!)
      int nextCarTime = 0;
      double arrivalStdDev = 0;
      double arrivalMean = 0;
      int eventID = 0;

//Scheduling the next vehicle:
      if (travelDir == "East")
      {
         arrivalMean = eastArrivalMean;
         arrivalStdDev = eastArrivalStdDev;
         eventID = EVENT_ARRIVE_EAST;
      }
      else if (travelDir == "West")
      {
         arrivalMean = westArrivalMean;
         arrivalStdDev = westArrivalStdDev;
         eventID = EVENT_ARRIVE_WEST;
      }
      else if (travelDir == "South")
      {
         arrivalMean = southArrivalMean;
         arrivalStdDev = southArrivalStdDev;
         eventID = EVENT_ARRIVE_SOUTH;
      }
      else
      {
         arrivalMean = northArrivalMean;
         arrivalStdDev = northArrivalStdDev;
         eventID = EVENT_ARRIVE_NORTH;
      }

//Generating the arrival time of the next X-bound car:
      nextCarTime = getPositiveNormal(arrivalMean, arrivalStdDev) + currentTime;

//Scheduling the new arrival event:
      EventClass newArrival(nextCarTime, eventID);
      eventList.insertValue(newArrival);
      cout << "Time: " << currentTime;
      cout << " Scheduled Event Type: " << travelDir << "-Bound";
      cout << " Arrival Time: " << nextCarTime << endl;
   }
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
   cout << "Time: " << currentTime << " Scheduled Event Type: ";
   if (currentTime <= timeToStopSim)
   {
      int lightChangeEvent = 0;
      int lightChangeTime = 0;

//Determining the current state of the light:
      if (currentLight == LIGHT_GREEN_EW)
      {
         lightChangeEvent = EVENT_CHANGE_YELLOW_EW;
         lightChangeTime = currentTime + eastWestGreenTime;
         cout << "Light Change to EW Yellow Time: " << lightChangeTime << endl;
      }
      else if (currentLight == LIGHT_YELLOW_EW)
      {
         lightChangeEvent = EVENT_CHANGE_GREEN_NS;
         lightChangeTime = currentTime + eastWestYellowTime;
         cout << "Light Change to NS Green Time: " << lightChangeTime << endl;
      }
      else if (currentLight == LIGHT_GREEN_NS)
      {
         lightChangeEvent = EVENT_CHANGE_YELLOW_NS;
         lightChangeTime = currentTime + northSouthGreenTime;
         cout << "Light Change to NS Yellow Time: " << lightChangeTime << endl;
      }
      else
      {
         lightChangeEvent = EVENT_CHANGE_GREEN_EW;
         lightChangeTime = currentTime + northSouthYellowTime;
         cout << "Light Change to EW Green Time: " << lightChangeTime << endl;
      }

//Generating the next light change event and adding it to the list:
      EventClass newLightChange(lightChangeTime, lightChangeEvent);
      eventList.insertValue(newLightChange);
   }
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
//Initializing the current event:
   EventClass currentEvent;
   eventList.removeFront(currentEvent);
   int eventType = currentEvent.getType();
   int eventTime = currentEvent.getTimeOccurs();
   currentTime = eventTime;

   if (currentTime > timeToStopSim)
      return false;
   else
   {
      cout << "\nHandling Event Type: ";

//This function operates on the next event depending on the event type:
//If the event is a car arrival:
      if (eventType == EVENT_ARRIVE_EAST || eventType == EVENT_ARRIVE_NORTH
         || eventType == EVENT_ARRIVE_SOUTH || eventType == EVENT_ARRIVE_WEST)
      {
         string travelDir;

//Assigning Travel Direction to Car and queueing that car, printing some data:
         if (eventType == EVENT_ARRIVE_EAST)
         {
            travelDir = EAST_DIRECTION;
            cout << travelDir << "-Bound Arrival Time: ";
            cout << eventTime << endl;

            CarClass newCar(travelDir, eventTime);
            eastQueue.enqueue(newCar);
            cout << "Time: " << currentTime << " Car #" << newCar.getId();
            cout << " arrives " << travelDir << "-bound - ";
            cout << "queue length: " << eastQueue.getNumElems() << endl;

//Checking if this is the longest the queue has been:
            if (eastQueue.getNumElems() > maxEastQueueLength)
            {
               maxEastQueueLength = eastQueue.getNumElems();
            }

//Scheduling next arrival:
            scheduleArrival(EAST_DIRECTION);

         }
         else if (eventType == EVENT_ARRIVE_WEST)
         {
            travelDir = WEST_DIRECTION;
            cout << travelDir << "-Bound Arrival Time: ";
            cout << eventTime << endl;

            CarClass newCar(travelDir, eventTime);
            westQueue.enqueue(newCar);
            cout << "Time: " << currentTime << " Car #" << newCar.getId();
            cout << " arrives " << travelDir << "-bound - ";
            cout << "queue length: " << westQueue.getNumElems() << endl;

//Checking if this is the longest the queue has been:
            if (westQueue.getNumElems() > maxWestQueueLength)
            {
               maxWestQueueLength = westQueue.getNumElems();
            }

//Scheduling next arrival:
            scheduleArrival(WEST_DIRECTION);
         }
         else if (eventType == EVENT_ARRIVE_NORTH)
         {
            travelDir = NORTH_DIRECTION;
            cout << travelDir << "-Bound Arrival Time: ";
            cout << eventTime << endl;

            CarClass newCar(travelDir, eventTime);
            northQueue.enqueue(newCar);
            cout << "Time: " << currentTime << " Car #" << newCar.getId();
            cout << " arrives " << travelDir << "-bound - ";
            cout << "queue length: " << northQueue.getNumElems() << endl;

//Checking if this is the longest the queue has been:
            if (northQueue.getNumElems() > maxNorthQueueLength)
            {
               maxNorthQueueLength = northQueue.getNumElems();
            }

//Scheduling next arrival:
            scheduleArrival(NORTH_DIRECTION);
         }
         else
         {
            travelDir = SOUTH_DIRECTION;
            cout << travelDir << "-Bound Arrival Time: ";
            cout << eventTime << endl;

            CarClass newCar(travelDir, eventTime);
            southQueue.enqueue(newCar);
            cout << "Time: " << currentTime << " Car #" << newCar.getId();
            cout << " arrives " << travelDir << "-bound - ";
            cout << "queue length: " << southQueue.getNumElems() << endl;

//Checking if this is the longest the queue has been:
            if (southQueue.getNumElems() > maxSouthQueueLength)
            {
               maxSouthQueueLength = southQueue.getNumElems();
            }

//Scheduling next arrival:
            scheduleArrival(SOUTH_DIRECTION);
         }
//At this point, the list of events has been re-updated, and the queue for
//the current time-step car has also been added to.
      }

//If the event is a light change:
      else if (eventType == EVENT_CHANGE_GREEN_EW
         || eventType == EVENT_CHANGE_GREEN_NS
         || eventType == EVENT_CHANGE_YELLOW_EW
         || eventType == EVENT_CHANGE_YELLOW_NS)
      {

//Number of cars that can make it through in the time span:
         int numCarsAllowed = 0;
         const int EMPTY_QUEUE = 0;

//Printing the event:
         cout << "Light Change to ";

//In this case, we can count how many cars have passed through the light
//While the North-South light was yellow:
         if (eventType == EVENT_CHANGE_GREEN_EW)
         {
            bool carDrivesOnYellow = true;
            numCarsAllowed = northSouthYellowTime;
            int numCarsThroughN = 0;
            int numCarsThroughS = 0;
            double carAdvancesCheck = 0;

//Updating current light:
            currentLight = LIGHT_GREEN_EW;

//Event Print:
            cout << "EW Green Time: " << currentTime << endl;
            cout << "Advancing cars on north-south yellow" << endl;

//First advancing Cars North:
            while (carDrivesOnYellow && (numCarsThroughN < numCarsAllowed)
               && (northQueue.getNumElems() > EMPTY_QUEUE))
            {
               carAdvancesCheck = getUniform(0, 100);
               if (carAdvancesCheck <= percentCarsAdvanceOnYellow)
               {
                  cout << "  Next north-bound car will ";
                  cout << "advance on yellow" << endl;
                  CarClass carToAdvance;
                  northQueue.dequeue(carToAdvance);
                  numTotalAdvancedNorth++;
                  numCarsThroughN++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances north-bound" << endl;
               }
               else
               {
                  cout << "  Next north-bound car will NOT ";
                  cout << "advance on yellow" << endl;
                  carDrivesOnYellow = false;
               }
            }
            if ((northQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughN == 0))
            {
                  cout << "  No north-bound cars waiting to ";
                  cout << "advance on yellow" << endl;
            }

//Next advancing Cars South, resetting counters:
            carDrivesOnYellow = true;
            carAdvancesCheck = 0;

            while (carDrivesOnYellow && (numCarsThroughS < numCarsAllowed)
               && (southQueue.getNumElems() > EMPTY_QUEUE))
            {
               carAdvancesCheck = getUniform(0, 100);
               if (carAdvancesCheck <= percentCarsAdvanceOnYellow)
               {
                  cout << "  Next south-bound car will ";
                  cout << "advance on yellow" << endl;
                  CarClass carToAdvance;
                  southQueue.dequeue(carToAdvance);
                  numTotalAdvancedSouth++;
                  numCarsThroughS++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances south-bound" << endl;
               }
               else
               {
                  cout << "  Next south-bound car will NOT ";
                  cout << "advance on yellow" << endl;
                  carDrivesOnYellow = false;
               }
            }

            if ((southQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughS == 0))
            {
                  cout << "  No south-bound cars waiting to ";
                  cout << "advance on yellow" << endl;
            }

            cout << "North-bound cars advanced on yellow: ";
            cout << numCarsThroughN;
            cout << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on yellow: ";
            cout << numCarsThroughS;
            cout << " Remaining queue: " << southQueue.getNumElems() << endl;
         }

//In this case, we can count how many cars have passed through the light
//While the East-West light was yellow:
         else if (eventType == EVENT_CHANGE_GREEN_NS)
         {
            bool carDrivesOnYellow = true;
            numCarsAllowed = eastWestYellowTime;
            int numCarsThroughE = 0;
            int numCarsThroughW = 0;
            double carAdvancesCheck = 0;

//Updating current light:
            currentLight = LIGHT_GREEN_NS;

//Event Print:
            cout << "NS Green Time: " << currentTime << endl;
            cout << "Advancing cars on east-west yellow" << endl;

//First advancing Cars East:
            while (carDrivesOnYellow && (numCarsThroughE < numCarsAllowed)
               && (eastQueue.getNumElems() > EMPTY_QUEUE))
            {
               carAdvancesCheck = getUniform(0, 100);
               if (carAdvancesCheck <= percentCarsAdvanceOnYellow)
               {
                  cout << "  Next east-bound car will ";
                  cout << "advance on yellow" << endl;
                  CarClass carToAdvance;
                  eastQueue.dequeue(carToAdvance);
                  numTotalAdvancedEast++;
                  numCarsThroughE++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances east-bound" << endl;
               }
               else
               {
                  cout << "  Next east-bound car will NOT ";
                  cout << "advance on yellow" << endl;
                  carDrivesOnYellow = false;
               }
            }
            if ((eastQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughE == 0))
            {
                  cout << "  No east-bound cars waiting to ";
                  cout << "advance on yellow" << endl;
            }

//Next advancing Cars West, resetting counters:
            carDrivesOnYellow = true;
            carAdvancesCheck = 0;
            while (carDrivesOnYellow && (numCarsThroughW < numCarsAllowed)
               && (westQueue.getNumElems() > EMPTY_QUEUE))
            {
               carAdvancesCheck = getUniform(0, 100);
               if (carAdvancesCheck <= percentCarsAdvanceOnYellow)
               {
                  cout << "  Next south-bound car will ";
                  cout << "advance on yellow" << endl;
                  CarClass carToAdvance;
                  westQueue.dequeue(carToAdvance);
                  numTotalAdvancedWest++;
                  numCarsThroughW++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances west-bound" << endl;
               }
               else
               {
                  cout << "  Next west-bound car will NOT ";
                  cout << "advance on yellow" << endl;
                  carDrivesOnYellow = false;
               }
            }
            if ((westQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughW == 0))
            {
                  cout << "  No west-bound cars waiting to ";
                  cout << "advance on yellow" << endl;
            }

               cout << "East-bound cars advanced on yellow: ";
               cout << numCarsThroughE;
               cout << " Remaining queue: " << eastQueue.getNumElems() << endl;
               cout << "West-bound cars advanced on yellow: ";
               cout << numCarsThroughW;
               cout << " Remaining queue: " << westQueue.getNumElems() << endl;
         }

//In this case, we count how many cars pass through the light while it's green.
//This if is specifically for the event where the light was EW Green:
         else if (eventType == EVENT_CHANGE_YELLOW_EW)
         {

//First, for cars advancing East:
            int numCarsThroughE = 0;
            int numCarsThroughW = 0;
            numCarsAllowed = eastWestGreenTime;

//Updating current light:
            currentLight = LIGHT_YELLOW_EW;

//Event Print:
            cout << "EW Yellow Time: " << currentTime << endl;
            cout << "Advancing cars on east-west green" << endl;

            while ((numCarsThroughE < numCarsAllowed)
               && (eastQueue.getNumElems() > EMPTY_QUEUE))
            {
               CarClass carToAdvance;
               eastQueue.dequeue(carToAdvance);
               numTotalAdvancedEast++;
               numCarsThroughE++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances east-bound" << endl;
            }
            if ((eastQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughE == 0))
            {
                  cout << "  No east-bound cars waiting to ";
                  cout << "advance on green" << endl;
            }
//Now, for cars advancing West:
            while ((numCarsThroughW < numCarsAllowed)
               && (westQueue.getNumElems() > EMPTY_QUEUE))
            {
               CarClass carToAdvance;
               westQueue.dequeue(carToAdvance);
               numTotalAdvancedWest++;
               numCarsThroughW++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances west-bound" << endl;
            }
            if ((westQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughW == 0))
            {
                  cout << "  No west-bound cars waiting to ";
                  cout << "advance on green" << endl;
            }

            cout << "East-bound cars advanced on green: ";
            cout << numCarsThroughE;
            cout << " Remaining queue: " << eastQueue.getNumElems() << endl;
            cout << "West-bound cars advanced on green: ";
            cout << numCarsThroughW;
            cout << " Remaining queue: " << westQueue.getNumElems() << endl;
         }

//In this case, we count how many cars pass through the light while it's green.
//This if is specifically for the event where the light was NS Green:
         else if (eventType == EVENT_CHANGE_YELLOW_NS)
         {

//First, for cars advancing North:
            int numCarsThroughN = 0;
            int numCarsThroughS = 0;
            numCarsAllowed = northSouthGreenTime;

//Updating current light:
            currentLight = LIGHT_YELLOW_NS;

//Event Print:
            cout << "NS Yellow Time: " << currentTime << endl;
            cout << "Advancing cars on north-south green" << endl;

            while ((numCarsThroughN < numCarsAllowed)
               && (northQueue.getNumElems() > EMPTY_QUEUE))
            {
               CarClass carToAdvance;
               northQueue.dequeue(carToAdvance);
               numTotalAdvancedNorth++;
               numCarsThroughN++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances north-bound" << endl;
            }
            if ((northQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughN == 0))
            {
                  cout << "  No north-bound cars waiting to ";
                  cout << "advance on green" << endl;
            }

//Now, for cars advancing South:
            while ((numCarsThroughS < numCarsAllowed)
               && (southQueue.getNumElems() > EMPTY_QUEUE))
            {
               CarClass carToAdvance;
               southQueue.dequeue(carToAdvance);
               numTotalAdvancedSouth++;
               numCarsThroughS++;

//Printing the car Queue data:
                  cout << "  Car # " << carToAdvance.getId();
                  cout << " advances south-bound" << endl;
            }
            if ((southQueue.getNumElems() == EMPTY_QUEUE)
               && (numCarsThroughS == 0))
            {
                  cout << "  No south-bound cars waiting to ";
                  cout << "advance on green" << endl;
            }

            cout << "North-bound cars advanced on yellow: ";
            cout << numCarsThroughN;
            cout << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on yellow: ";
            cout << numCarsThroughS;
            cout << " Remaining queue: " << southQueue.getNumElems() << endl;
         }

//Finally, scheduling the next light change:
         scheduleLightChange();
      }

//In this case, the time has not exceeded simulation time, so return true:
      return true;
   }
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
