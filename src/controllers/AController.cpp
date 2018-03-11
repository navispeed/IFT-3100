//
// Created by Grégoire GUEMAS on 18-02-15.
//

#include <events/ofEventUtils.h>
#include "AController.h"
#include "ofSystemUtils.h"

void AController::enableEvents() {
}

void AController::disableEvents() {

}

void AController::showError(const std::string &message)
{
	ofSystemAlertDialog(message);
}
