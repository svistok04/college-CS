import logging, warnings
import torch

from pathlib import Path
from transformers import AutoModelForCausalLM, AutoTokenizer
logging.getLogger('transformers').setLevel(logging.ERROR)
warnings.filterwarnings('ignore')
class Chatboot:
    def __init__(self, model_dir: Path = Path("./models/Llama-3.2-1B-Instruct")):
        """
        Initializes the chatbot with a locally stored LLaMA model.
        """
        model_dir = Path(model_dir)
        if not model_dir.exists():
            raise FileNotFoundError(f"Model directory not found: {model_dir}")

        # System instruction
        self.system_instruction = (
            "You are a helpful and concise assistant. Answer based on the user's input. "
            "Answer in a maximum of 30 words."
            "Do not repeat or invent unrelated information.\n\n"
        )
        self.conversation_history = ""

        # Load tokenizer and model from the local directory
        self.proc = AutoTokenizer.from_pretrained(model_dir, use_fast=False)
        self.model = AutoModelForCausalLM.from_pretrained(model_dir)

    def __call__(self, user_input: str):

        if not user_input.strip():  # Checks for empty string or string with only whitespace
            assistant_response = "I'm sorry, could you clarify your question?"
            # Update history with the placeholder response
            self.conversation_history += f"User: {user_input}\nAssistant: {assistant_response}\n"
            return assistant_response

        # Trim history to avoid excessive context
        self.conversation_history = "\n".join(self.conversation_history.split("\n")[-6:])

        prompt = (
                self.system_instruction
                + "\nHere is the conversation history (for context, do not include it in the answer):\n"
                + self.conversation_history
                + "\nCurrent Query from User:\n"
                + f"{user_input}\n"
        )

        # Encode prompt and generate response
        input_ids = self.proc.encode(prompt, return_tensors="pt")
        output_ids = self.model.generate(
            input_ids,
            max_new_tokens=46,
            pad_token_id=self.proc.eos_token_id,
            temperature=0.2,
            top_p=0.8
        )

        # Decode response
        response = self.proc.decode(output_ids[0], skip_special_tokens=True)
        assistant_response = response.split("Assistant:")[-1].strip()

        # if assistant_response in self.conversation_history:
        #     assistant_response = "I'm sorry, could you clarify your question?"

        if "User:" in assistant_response or "Assistant:" in assistant_response:
            assistant_response = "I'm sorry, could you clarify your question?"

    # Update history
        self.conversation_history += f"User: {user_input}\nAssistant: {assistant_response}\n"

        return assistant_response


if __name__ == "__main__":
    torch.set_num_threads(20)
    chatboot = Chatboot()
    print("Chatbot is ready! Type 'exit' to end the conversation.\n")
    print("Chatbot: Hi! How can I help you today?\n")

    while True:
        user_input = input("You: ")
        if user_input.lower() in ["exit", "quit"]:
            print("\nChatbot: Goodbye! Have a great day!\n")
            break

        response = chatboot(user_input)
        print(f"Chatbot: {response}\n")


#
# import torch
# from transformers import AutoModelForSeq2SeqLM, AutoTokenizer, T5Tokenizer, T5ForConditionalGeneration, AutoModelForCausalLM
#
# class Chatboot:
#     def __init__(self, model_dir: str = "./models/Llama-3.2-1B-Instruct"):
#         # Load tokenizer and model from the local directory
#         self.tokenizer = AutoTokenizer.from_pretrained(model_dir, use_fast=False)
#         self.tokenizer.pad_token = self.tokenizer.eos_token  # Ensure pad token is defined
#         self.model = AutoModelForCausalLM.from_pretrained(
#             model_dir,
#             low_cpu_mem_usage=True,  # Optimizes memory usage for CPU
#         )
#
#     def __call__(self, question: str):
#         # Encode the question with attention mask
#         inputs = self.tokenizer(question, return_tensors="pt", padding=True, truncation=True)
#         attention_mask = inputs.attention_mask
#
#         # Generate response with attention mask
#         outputs = self.model.generate(
#             inputs.input_ids,
#             attention_mask=attention_mask,  # Explicitly pass the attention mask
#             max_length=512,
#             temperature=0.7,
#             top_p=0.95,
#             pad_token_id=self.tokenizer.eos_token_id,
#         )
#         answer = self.tokenizer.decode(outputs[0], skip_special_tokens=True)
#         return answer
#
#
# # Example usage
# if __name__ == "__main__":
#     chatboot = Chatboot()
#
#     question = "What is the latest on AI advancements?"
#     question = "help me"
#     answer = chatboot(question)
#
#     print(f"Question: {question}")
#     print(f"Answer: {answer}")
