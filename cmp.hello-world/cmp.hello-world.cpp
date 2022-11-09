/// @file
///	@ingroup    cmp4
///	@copyright	Copyright 2022 Gangil Yi(giy.hands@gmail.com). All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"

using namespace c74::min;


class hello_world : public object<hello_world> {
private:
    size_t  m_sr;
    size_t  m_vs;
    
public:
    MIN_DESCRIPTION	{" "};
    MIN_TAGS		{"utilities"};
    MIN_AUTHOR		{"Gangil Yi"};
    MIN_RELATED		{" "};

    inlet<>  input	{ this, "(bang) post greeting to the max console" };
//    outlet<> output	{ this, "(anything) output the message which is posted to the max console" };
    outlet<> output { this, "(signal) output", "signal" };


    // define an optional argument for setting the message
    argument<symbol> greeting_arg { this, "greeting", "Initial value for the greeting attribute.",
        MIN_ARGUMENT_FUNCTION {
            greeting = arg;
        }
    };


    // the actual attribute for the message
    attribute<symbol> greeting { this, "greeting", "hello world",
        description {
            "Greeting to be posted. "
            "The greeting will be posted to the Max console when a bang is received."
        }
    };


    // respond to the bang message to do something
    message<> bang { this, "bang", "Post the greeting.",
        MIN_FUNCTION {
            symbol the_greeting = greeting;    // fetch the symbol itself from the attribute named greeting

            cout << the_greeting << endl;    // post to the max console
            output.send(the_greeting);       // send out our outlet
            return {};
        }
    };

    message<> dspsetup{ this, "dsp_setup",
        MIN_FUNCTION {
            m_sr = args[0];
            m_vs = args[1];
            cout << "Sample Rate: " << m_sr << " / Signal Vector Size: " << m_vs << endl;
            return {};
        }
    };



    // post to max window == but only when the class is loaded the first time
    message<> maxclass_setup { this, "maxclass_setup",
        MIN_FUNCTION {
            cout << "hello world" << endl;
            return {};
        }
    };

};


MIN_EXTERNAL(hello_world);
