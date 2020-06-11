install(FILES algorithm CurrentPulse.h NeuronBase.h CurrentSource.h DirectSynapsis.h
		SigmoidalDirectSynapsis.h DiffusionSynapsis.h #DiscreteDiffusionSynapse.h
		ElectricalSynapsis.h analysis.h
		DESTINATION ${PROJECT_NAME}/${PROJECT_VERSION}/include)
