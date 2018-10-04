# TypeScripts

```ts
// tslint:disable:max-line-length
/**
 * Debounce
 * @param wait millisecond delay
 * @param immediate sets if we want to "call the function then stall for x milliseconds before allowing it to be called again",or "stall for x milliseconds then actually call the function"
 * @return PropertyDecorator
 * @example
 * => @Debounce(500)
 */
export default function Debounce(wait: number, immediate: boolean = false) {
    return (target: any, propertyKey: string | symbol, descriptor: PropertyDescriptor) => {
        let timeout: any
        const originalMethod = descriptor.value
        descriptor.value = function() {
            const context = this
            const args = arguments
            const later = () => {
                timeout = null
                if (!immediate) {
                    originalMethod.apply(context, args)
                }
            }
            const callNow = immediate && !timeout
            clearTimeout(timeout)
            timeout = setTimeout(later, wait)
            if (callNow) {
                originalMethod.apply(context, args)
            }
        }
        return descriptor
    }
}
```