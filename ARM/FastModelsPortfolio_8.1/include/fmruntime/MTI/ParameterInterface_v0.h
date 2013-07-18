/*!
 *  \file   ParameterInterface_v0.h
 *  \brief  The runtime MTI::ParameterInterface, version 0.
 *  \date   Copyright ARM Limited 2008-2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  ParameterInterface.h header should be included instead.
 */

#include "eslapi/CAInterface.h"
#include "eslapi/CADITypes.h"

namespace MTI
{

namespace v0
{

class ParameterInterface :
    public eslapi::CAInterface
{
public:
    /// Static helper method to return the interface name for the 
    /// CAInterface.
    static eslapi::if_name_t IFNAME() { return "ParameterInterface0"; }
    
    /// Static helper method to return the current interface revision 
    /// for the CAInterface.
    static eslapi::if_rev_t IFREVISION() { return 0; }

    /**
     * Get list of supported parameters and parameter information.
     * 
     * \param[in] startIndex The index of the first parameter. Not a parameter id !
     *
     * \param[in] desiredNumOfParams The maximum number of parameters this call should return.
     *
     * \param[out] actualNumOfParams The number of parameter infos
     * returned by the call. If this is smaller than
     * desiredNumOfParams and the return value is CADI_STATUS_OK then
     * there end of the parameter list has been reached. If this is
     * equal to desiredNumOfParams there are more parameter infos for
     * which another call should be made, likely with startIndex
     * increased by actualNumOfParams.
     *
     * \param[out] params A field that will contain the parameter infos
     * after the call. The array is provided by the caller and must be
     * large enough to contain desiredNumOfParams parameter infos.
     */
    virtual eslapi::CADIReturn_t GetParameterInfos(uint32_t startIndex,
                                                   uint32_t desiredNumOfParams,
                                                   uint32_t *actualNumOfParams,
                                                   eslapi::CADIParameterInfo_t *params) = 0;

    /** Get parameter info for a specific parameter name.
     *
     * \param[in] parameterName Name of the parameter to be
     * retrieved. This is the 'local' name in the model, not the
     * global hierarchical name.
     *
     * \param[out] param Points to a single CADIParameterInfo_t buffer
     * which should be preinitialized by the caller and filled with
     * data by the callee.
     */
    virtual eslapi::CADIReturn_t GetParameterInfo(const char *parameterName,
                                                  eslapi::CADIParameterInfo_t *param) = 0;

    /** Get current parameter values.
     *
     * \param[in] parameterCount
     *            Length of array paramValuesOut.
     *
     * \param[out] actualNumOfParamsRead
     *            Number of valid entries in paramValuesOut. Should be initialized to 0 by caller. If an error is returned
     *            and this is > 0 then the first actualNumOfParams entries are valid and caused no error. In this case the
     *            entry paramValuesOut[actualNumOfParamsRead] caused the error.
     *
     * \param[out] paramValuesOut
     *            Output buffer of parameter values.
     */
    virtual eslapi::CADIReturn_t GetParameterValues(uint32_t parameterCount,
                                                    uint32_t *actualNumOfParamsRead,
                                                    eslapi::CADIParameterValue_t *paramValuesOut) = 0;
    /** Set the parameters to new values.
     * 
     * \param[in] parameterCount Number of parameters for which a new
     * value should be set. Can be a subset of the parameters reported
     * via GetParameterInfos.
     *
     * \param parameters An error of parameter values. Allocated by
     * the called, must contain as many entries as parameterCount
     * specifies.
     *
     * \param[out] error Can be used to return an error message.
     */

    virtual eslapi::CADIReturn_t SetParameterValues(uint32_t parameterCount,
                                                    eslapi::CADIParameterValue_t *parameters,
                                                    eslapi::CADIFactoryErrorMessage_t *error) = 0;
};

} // namespace v0

} // namespace MTI

// End of file ParameterInterface_v0.h
