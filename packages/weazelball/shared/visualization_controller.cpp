#include <gazebo/gazebo.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/common.hh>
#include <gazebo/common/Events.hh>
#include <gazebo/physics/physics.hh>

#include "models.h"
#include "weazelball.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <Reveal/core/pointers.h>
#include <Reveal/core/state.h>
#undef DATA_GENERATION   // TODO: remove when debugged
#include <sstream>

#define PI 3.14159265359

//-----------------------------------------------------------------------------
// set on the interval [0,9] to switch between different vicon motion capture
// sessions.
unsigned trialid = 9;

double vicon_sample_rate = 100.0;      // set in software for these experiments

//-----------------------------------------------------------------------------

class log_c {
private:
  std::string   _name;
  std::ofstream _file;
public:
  log_c( std::string name ) { _name = name; }
  virtual ~log_c( void ) { close(); }

  bool open( void ) {
    _file.open( _name.c_str(), std::ios::out | std::ios::trunc );
    if( !_file.is_open() ) return false;
    return true;
  }

  void close( void ) {
    if( _file.is_open() ) _file.close();
  }
  
  bool write( std::string data ) {
    if( !_file.is_open() ) return false;
    _file << data;
    return true;
  }
};
typedef boost::shared_ptr<log_c> log_ptr;

//-----------------------------------------------------------------------------
class state_c {
public:
  state_c( void ) {
    _t = 0.0;
    for( unsigned i = 0; i < size(); i++ ) _x[i] = 0.0;
    _x[3] = 1.0;  // normalize w coordinate
  }
  virtual ~state_c( void ) {}

private:
  double _x[7];
  double _t;

public:
  unsigned size( void ) const {
    return 7;
  }

  double t( void ) {
    return _t;
  }

  void t( double t_ ) {
    _t = t_;
  }

  void t( int min, int sec, int ms ) {
    _t = (double)min * 60.0 + (double)sec + (double)ms/1000.0;
  }

  double& val( unsigned i ) { 
    assert( i < size() );
    return _x[i];
  }

  const double& val( unsigned i ) const { 
    assert( i < size() );
    return _x[i];
  }

  double& operator[]( unsigned i ) { 
    assert( i < size() );
    return _x[i];
  }

  const double& operator[]( unsigned i ) const { 
    assert( i < size() );
    return _x[i];
  }

  void print( void ) {
    printf( "state{ t[%f] x{", _t );
    for( unsigned i = 0; i < size(); i++ ) {
      if( i > 0 ) printf( ", " );
      printf( "%f", _x[i] );
    }
    printf( "}}" );
  }
};

typedef boost::shared_ptr<state_c> state_ptr;

//-----------------------------------------------------------------------------
namespace gazebo 
{
  class controller_c : public ModelPlugin
  {
  private:
    event::ConnectionPtr _updateConnection;

    world_ptr _world;
    weazelball_ptr _weazelball;

    log_ptr log;

    //std::vector<state_ptr> _states;
    wb_vicon_data_ptr _wb_vicon_data;

    log_ptr state_log;
    //log_ptr stats_log;
  public:
    //-------------------------------------------------------------------------
    controller_c( void ) { }

    //-------------------------------------------------------------------------
    virtual ~controller_c( void ) {
      if( log ) log->close();

      event::Events::DisconnectWorldUpdateBegin( _updateConnection );
 
      _world->close();
    }

    //-------------------------------------------------------------------------
    // Gazebo callback.  Called when the simulation is starting up
    virtual void Load( physics::ModelPtr model, sdf::ElementPtr sdf ) {

      std::string validation_errors;
      _world = world_ptr( new world_c( model->GetWorld() ) );
      if( !_world->validate( validation_errors ) ) {
        printf( "Unable to validate world in controller\n%s\nERROR: Plugin failed to load\n", validation_errors.c_str() );
        return;
      }

      // open the world before we begin
      _world->open();

      // get references to objects in the world
      _weazelball = _world->weazelball();
   
      // -- CALLBACKS --
      _updateConnection = event::Events::ConnectWorldUpdateBegin(
        boost::bind( &controller_c::Update, this ) );

      _wb_vicon_data = wb_vicon_data_ptr( new wb_vicon_data_c() );
      _wb_vicon_data->load_mocap();

      std::stringstream state_log_name;
      state_log_name << "trial_" << trialid << ".log";
      state_log = log_ptr( new log_c( state_log_name.str() ) );
      if( !state_log || !state_log->open() ) {
        printf( "ERROR: unable to open state log for writing\nPlugin failed to load\n" );
        return;
      }
/*
      std::stringstream stats_log_name;
      stats_log_name << "stats_" << trialid << ".log";
      stats_log = log_ptr( new log_c( stats_log_name.str() ) );
      if( !stats_log || !stats_log->open() ) {
        printf( "ERROR: unable to open stats log for writing\nPlugin failed to load\n" );
        return;
      }
*/
      log = log_ptr( new log_c( "out.log" ) );
      if( !log || !log->open() ) {
        printf( "ERROR: unable to open output log\nPlugin failed to load\n" );
        return;
      }

      // -- FIN --
      printf( "controller has initialized\n" );
  
    }

    //-------------------------------------------------------------------------
    // Gazebo callback.  Called whenever the simulation advances a timestep
    virtual void Update( ) {

      static std::vector< std::vector<double> > vicon_data_stats(10);

      
      static unsigned calls = 0;
      static unsigned current_state_idx = 0;

      //static double max_vicon_latency = std::numeric_limits<double>::min();
      //static double min_vicon_latency = std::numeric_limits<double>::max();
      //static unsigned zero_latency_count = 0;

      static bool first_state = true;

      //static double last_vicon_time = 0.0;
      static double sim_time = 0.0; 
      static double last_sim_time = 0.0;
      static double adjusted_vicon_time = 0.0; 
      static double initial_vicon_time = 0.0;

      static unsigned motor_cycles = 0;
      static double last_theta = 0.0;

      gazebo::math::Vector3 pos;
      gazebo::math::Quaternion rot;

      if( calls == 0 ) {
        if( current_state_idx == _wb_vicon_data->states[trialid].size() ) {
          //log aggregated stats
/*
          double avg_latency = sim_time / current_state_idx;

          std::stringstream stats;
          stats << current_state_idx << " ";
          stats << min_vicon_latency << " ";
          stats << max_vicon_latency << " ";
          stats << zero_latency_count << " ";
          stats << avg_latency << std::endl;

          stats_log->write( stats.str() );
*/

//          vicon_data_stats[trialid].push_back( current_state_idx );
//          vicon_data_stats[trialid].push_back( min_vicon_latency );
//          vicon_data_stats[trialid].push_back( max_vicon_latency );
//          vicon_data_stats[trialid].push_back( (double) zero_latency_count );
//          double avg_latency = sim_time / current_state_idx;
//          vicon_data_stats[trialid].push_back( avg_latency );

//          if( trialid < 9 ) {
//            trialid++;
//            current_state_idx = 0;

//            max_vicon_latency = std::numeric_limits<double>::min();
//            min_vicon_latency = std::numeric_limits<double>::max();
//            last_vicon_time = 0.0;
//            first_state = true;
//            zero_latency_count = 0;
//            vicon_time = 0.0; 
//            sim_time = 0.0; 
//            motor_cycles = 0;
//            last_theta = 0.0;
//          } else {

//          for( unsigned i = 0; i < vicon_data_stats.size(); i++ ) {
//            printf( "trial[%u], ", i );
//            printf( "states[%u], ", (unsigned) vicon_data_stats[i][0] );
//            printf( "min_vicon_latency[%f], ", vicon_data_stats[i][1] );
//            printf( "max_vicon_latency[%f], ", vicon_data_stats[i][2] );
//            printf( "zero_latency_count[%u], ", (unsigned) vicon_data_stats[i][3] );
//            printf( "avg_latency[%f]\n", vicon_data_stats[i][4] );
//          }

          // kills the simulation
          state_log->close();
//          stats_log->close();
          exit(0);
//        }
        }

        wb_vicon_state_ptr state = _wb_vicon_data->states[trialid].at( current_state_idx++ );

        pos = gazebo::math::Vector3( state->val(0), state->val(1), state->val(2) );
        rot = gazebo::math::Quaternion( state->val(6), state->val(3), state->val(4), state->val(5) );
        // the vicon data is recorded with a model frame rotated by 90 degrees 
        // to the world frame.  Rotate the model frame back to a frame aligned
        // with the world.
        rot = rot * gazebo::math::Quaternion( -PI/2.0, 0.0, 0.0 );

        gazebo::math::Pose pose( pos, rot );

        _weazelball->model()->SetLinkWorldPose( pose, _weazelball->shell() );

        if( !first_state ) {
          double dt = 1.0 / vicon_sample_rate;
          sim_time += dt;
        } else {
          initial_vicon_time = state->t();
        }
        adjusted_vicon_time = state->t() - initial_vicon_time;
/*
        if( !first_state ) {

          double dt = vicon_time - last_vicon_time;

          if( dt > max_vicon_latency ) 
            max_vicon_latency = dt;
          if( dt < min_vicon_latency && dt > 0.0 ) 
            min_vicon_latency = dt;

          if( dt == 0.0 ) zero_latency_count++;

          //printf( "state->t[%f], last_time[%f], max_vicon_latency[%f], min_vicon_latency[%f], zero_latency_count[%u]\n", state->t(), last_time, max_vicon_latency, min_vicon_latency, zero_latency_count );

          sim_time += dt;
        }
*/
        //_world->sim_time( state->t() );
        _world->sim_time( sim_time );
        //printf( "vicon_time[%f], sim_time[%f]\n", vicon_time, sim_time );

        //last_vicon_time = state->t();
        last_sim_time = sim_time;
      } else {
        //if( calls >= 25 ) {
        if( calls >= 1 ) {
          calls = 0;
          return;
        }
      }

      double theta;
      double motor_freq = WEAZELBALL_MOTOR_HZ;
      double theta_at_sim_t_zero;

      // updating the internal state of the robot
      if( trialid == 0 ) {
        //theta_at_sim_t_zero = 2.8762;
        theta_at_sim_t_zero = 3.9623;
      } else if( trialid == 1 ) {
        theta_at_sim_t_zero = 3.5203;
      } else if( trialid == 2 ) {
        theta_at_sim_t_zero = 1.7233;
      } else if( trialid == 3 ) {
        theta_at_sim_t_zero = 5.3984;
      } else if( trialid == 4 ) {
        theta_at_sim_t_zero = 1.5870;
      } else if( trialid == 5 ) {
        theta_at_sim_t_zero = 4.9115;
      } else if( trialid == 6 ) {
        theta_at_sim_t_zero = 2.1809;
      } else if( trialid == 7 ) {
        theta_at_sim_t_zero = 4.6411;
      } else if( trialid == 8 ) {
        theta_at_sim_t_zero = 5.4913;
      } else if( trialid == 9 ) {
        theta_at_sim_t_zero = 1.7763;
      }
      double omega = 2.0 * PI * motor_freq;  // radians per sec

      theta = sim_time * omega + theta_at_sim_t_zero;
      //theta -= ((double)((int)( theta / (2.0 * PI) )) * (2.0 * PI));
      while( theta - 2.0 * PI > 0.0 )
        theta -= 2.0 * PI;

      if( !first_state ) {
        if( last_theta + PI / 10.0 > 2.0 * PI && theta - PI / 10.0 < 0.0 )
          motor_cycles++;
      }

      last_theta = theta;
      //}


      printf( "sim_time[%f], vicon_time[%f]", sim_time, adjusted_vicon_time );
      printf( ", cycles[%u], theta[%f]\n", motor_cycles, theta );


      if( first_state ) first_state = false;

      if( calls == 0 ) {
        // log state

        std::stringstream data;
        data << sim_time << " ";
        data << adjusted_vicon_time << " ";
        data << pos.x << " " << pos.y << " " << pos.z << " ";
        data << rot.x << " " << rot.y << " " << rot.z << " " << rot.w << " ";
        data << theta << std::endl;       

        state_log->write( data.str() ); 
      }

      calls++;
    }

    //-------------------------------------------------------------------------
    // Gazebo callback.  Called whenever the simulation is reset
    virtual void Reset( ) { 
      
    }

  };

  GZ_REGISTER_MODEL_PLUGIN( controller_c )

} // namespace gazebo

//-----------------------------------------------------------------------------
