//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/protocol/c4soap/c4soap_message.hpp>
#include <core/protocol/c4soap/c4soap_director.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            bool
            is_async_c4soap(const std::string& soap)
            {
                c4soap_message msg(soap);

                return msg.is_async();
            }

            std::string
            authenticate_password(unsigned long& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "AuthenticatePassword", seq);
                c4soap_message::param(ss, "password", "string", "root");
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_version_info(unsigned long& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetVersionInfo", seq);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_director_info(unsigned long& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDirectorInfo", seq);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_devices_by_interface(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDevicesByInterface", seq);
                c4soap_message::param(ss, "GUID", "string", params[0]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_devices_by_c4i(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDevicesByC4i", seq);
                c4soap_message::param(ss, "c4i_name", "string", params[0]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            send_to_device(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;

                if (params.size() > 1)
                {
                    std::string id = params[0];
                    std::string cmd = params[1];

                    c4soap_message::begin_c4soap_message(ss, "SendToDevice", seq);
                    c4soap_message::param(ss, "iddevice", "number", id);
                    cmd = "<command>" + cmd + "</command>";
                    if (params.size() > 2)
                    {
                        std::string param = "";
                        for (size_t i = 2; i < params.size(); i++)
                        {
                            size_t j = i + 1;
                            if (j < params.size())
                            {
                                param += c4soap_message::get_param_value(params[i], params[j]);
                            }
                            else
                                break;
                        }
                        std::string params = "<params>" + param + "</params>";
                        cmd += params;
                    }
                    std::string device_command = "<devicecommand>" + cmd + "</devicecommand>";
                    c4soap_message::param(ss, "data", "string", device_command);
                    c4soap_message::end_c4soap_message(ss);
                }

                return ss.str();
            }

            std::string
            send_async_to_device(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;

                if (params.size() > 1)
                {
                    std::string id = params[0];
                    std::string cmd = params[1];

                    c4soap_message::begin_c4soap_async_message(ss, "SendToDevice", seq);
                    c4soap_message::param(ss, "iddevice", "number", id);
                    cmd = "<command>" + cmd + "</command>";
                    if (params.size() > 2)
                    {
                        std::string param = "";
                        for (size_t i = 2; i < params.size(); i++)
                        {
                            size_t j = i + 1;
                            if (j < params.size())
                            {
                                param += c4soap_message::get_param_value(params[i], params[j]);
                            }
                            else
                                break;
                        }
                        std::string params = "<params>" + param + "</params>";
                        cmd += params;
                    }
                    std::string device_command = "<devicecommand>" + cmd + "</devicecommand>";
                    c4soap_message::param(ss, "data", "string", device_command);
                    c4soap_message::end_c4soap_message(ss);
                }

                return ss.str();
            }

            // register an event listener
            std::string
            register_event_listener(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_async_message(ss, "RegisterEventListener", seq);
                c4soap_message::param(ss, "idevent", "ulong", params[0]);
                c4soap_message::param(ss, "iditem", "ulong", params[1]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            // unregister an event listener
            std::string
            unregister_event_listener(unsigned long& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_async_message(ss, "UnregisterEventListener", seq);
                c4soap_message::param(ss, "idevent", "ulong", params[0]);
                c4soap_message::param(ss, "iditem", "ulong", params[1]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }
        }
    }
}
