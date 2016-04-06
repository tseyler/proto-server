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
            std::string
            authenticate_password(int& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "AuthenticatePassword", seq);
                c4soap_message::param(ss, "password", "string", "root");
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_version_info(int& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetVersionInfo", seq);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_director_info(int& seq, const params_array& /*params*/)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDirectorInfo", seq);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_devices_by_interface(int& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDevicesByInterface", seq);
                c4soap_message::param(ss, "GUID", "string", params[0]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            get_devices_by_c4i(int& seq, const params_array& params)
            {
                std::stringstream ss;
                c4soap_message::begin_c4soap_message(ss, "GetDevicesByC4i", seq);
                c4soap_message::param(ss, "c4i_name", "string", params[0]);
                c4soap_message::end_c4soap_message(ss);

                return ss.str();
            }

            std::string
            send_to_device(int& seq, const params_array& params)
            {
                std::stringstream ss;

                if (params.size() > 1)
                {
                    std::string id = params[0];
                    std::string cmd = params[1];

                    c4soap_message::begin_c4soap_message(ss, "SendToDevice", seq);
                    c4soap_message::param(ss, "iddevice", "ulong", id);
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
                    std::string root = c4soap_message::get_param("root", "xml", cmd);
                    c4soap_message::param(ss, "data", "xml", root);
                    c4soap_message::end_c4soap_message(ss);
                }

                return ss.str();
            }
        }
    }
}
