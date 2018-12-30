
#ifndef FUNCTIONVALIDATOR_H
#define FUNCTIONVALIDATOR_H

#include ".\GtFunctionEvaluator.h"
namespace GT
{
	namespace GtCalc
	{
		class HTL_DLLAPI GtFunctionValidator
		{
		public:
			GtFunctionValidator(void);
			~GtFunctionValidator(void);

			bool ValidateExpression(const std::vector<GtToken> & arrObjTokenCollection);

			int ValidateOperator(const std::vector<GtToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);

			int ValidateFunction(const std::vector<GtToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos, int intNumArgs);

			//!NEG Function
			int ValidateNumber(const std::vector<GtToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);
			//!NEG Function
			int ValidateVariable(const std::vector<GtToken> & arrObjTokenCollection, bool & blnValidFunction, int intCurrPos);

		};
	}//end namespace GtCalc
}//end namespace GT
#endif